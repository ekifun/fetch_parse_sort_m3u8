#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <curl/curl.h>
#include "m3u8-cpp/include/m3u8/Parser.h"

enum SortMode {
    SORT_BY_BW,
    SORT_BY_RES
};

void sortStreamsByBandwidth(std::vector<std::shared_ptr<StreamItem>>& streams);
void sortStreamsByResolution(std::vector<std::shared_ptr<StreamItem>>& streams);

// libcurl write callback
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::string* buffer = static_cast<std::string*>(userp);
    buffer->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

std::string fetchM3U8(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
    }
    return response;
}

void parseAndGroupStreams(
    const std::string& playlistContent,
    std::map<std::string, std::vector<std::shared_ptr<MediaItem>>>& mediaByGroupId,
    std::map<std::string, std::vector<std::shared_ptr<StreamItem>>>& streamsByAudioGroup)
{
    M3UParser parser;
    auto m3u8 = std::make_shared<M3u8>();

    // Parse the playlist
    std::istringstream ss(playlistContent);
    std::string line;
    parser.setCallback(nullptr);  // No real-time callback needed
    while (std::getline(ss, line)) {
        parser.parse(line);
    }
    m3u8 = parser.m3u8();

    // Group media and streams
    for (const auto& [tagType, itemList] : m3u8->items) {
        for (const auto& item : itemList) {
            if (!item) continue;

            if (auto media = std::dynamic_pointer_cast<MediaItem>(item)) {
                const auto& attr = media->attributeList;
                if (attr.contains("GROUP-ID")) {
                    std::string groupId = attr.at("GROUP-ID").get<std::string>();
                    mediaByGroupId[groupId].push_back(media);
                }
            } else if (auto stream = std::dynamic_pointer_cast<StreamItem>(item)) {
                const auto& attr = stream->attributeList;
                if (attr.contains("AUDIO")) {
                    std::string audioGroup = attr.at("AUDIO").get<std::string>();
                    streamsByAudioGroup[audioGroup].push_back(stream);
                }
            }
        }
    }
}

void sortStreamsByBandwidth(std::vector<std::shared_ptr<StreamItem>>& streams) {
    std::sort(streams.begin(), streams.end(), [](const std::shared_ptr<StreamItem>& a,
                                                  const std::shared_ptr<StreamItem>& b) {
        auto& attrA = a->attributeList;
        auto& attrB = b->attributeList;

        int64_t bwA = attrA.contains("BANDWIDTH") ? attrA.get("BANDWIDTH").get<int64_t>() : 0;
        int64_t bwB = attrB.contains("BANDWIDTH") ? attrB.get("BANDWIDTH").get<int64_t>() : 0;

        return bwA > bwB;
    });
}

void sortStreamsByResolution(std::vector<std::shared_ptr<StreamItem>>& streams) {
    auto parseRes = [](const nlohmann::json& resVal) -> int64_t {
        
        try {
            int64_t w = resVal[0].get<int64_t>();
            int64_t h = resVal[1].get<int64_t>();
            return w * h;
        } catch (...) {
            return 0;
        }

        return 0;
    };

    std::sort(streams.begin(), streams.end(), [parseRes](const std::shared_ptr<StreamItem>& a,
                                                         const std::shared_ptr<StreamItem>& b) {
        auto& attrA = a->attributeList;
        auto& attrB = b->attributeList;

        int64_t resA = attrA.contains("RESOLUTION") ? parseRes(attrA.get("RESOLUTION")) : 0;
        int64_t resB = attrB.contains("RESOLUTION") ? parseRes(attrB.get("RESOLUTION")) : 0;

        return resA > resB;
    });
}

void printSortedStreamsForEachGroup(
    const std::map<std::string, std::vector<std::shared_ptr<MediaItem>>>& mediaByGroupId,
    const std::map<std::string, std::vector<std::shared_ptr<StreamItem>>>& streamsByAudioGroup)
{
    auto getIntFromJson = [](const nlohmann::json& val) -> int64_t {
        if (val.is_number_integer()) return val.get<int64_t>();
        if (val.is_string()) return std::stoll(val.get<std::string>());
        return 0;
    };

    std::cout << "\n====== GROUPED STREAMS BY AUDIO ======\n" << std::endl;

    for (const auto& [groupId, streams] : streamsByAudioGroup) {
        std::cout << "=== AUDIO GROUP: " << groupId << " ===" << std::endl;

        // Print associated media
        auto it = mediaByGroupId.find(groupId);
        if (it != mediaByGroupId.end()) {
            for (const auto& media : it->second) {
                const auto& attr = media->attributeList;
                std::cout << "MEDIA: NAME=\"" << attr.at("NAME").get<std::string>() << "\""
                          << ", URI=\"" << attr.at("URI").get<std::string>() << "\"";

                if (attr.contains("CHANNELS")) {
                    std::cout << ", CHANNELS=\"" << attr.at("CHANNELS").get<std::string>() << "\"";
                }
                if (attr.contains("LANGUAGE")) {
                    std::cout << ", LANGUAGE=\"" << attr.at("LANGUAGE").get<std::string>() << "\"";
                }
                std::cout << std::endl;
            }
        }

        // Print each stream
        for (const auto& stream : streams) {
            const auto& attr = stream->attributeList;
            std::cout << "  STREAM: BW=" << getIntFromJson(attr.at("BANDWIDTH"));

            if (attr.contains("RESOLUTION")) {
                const auto& res = attr.at("RESOLUTION");
                std::cout << ", RES=";
                if (res.is_string()) {
                    std::cout << res.get<std::string>();
                } else if (res.is_array() && res.size() == 2) {
                    std::cout << res[0] << "x" << res[1];
                } else {
                    std::cout << "N/A";
                }
            }

            if (attr.contains("CODECS")) {
                std::cout << ", CODECS=\"" << attr.at("CODECS").get<std::string>() << "\"";
            }

            if (stream->get("uri").is_string()) {
                std::cout << ", URI=\"" << stream->get("uri").get<std::string>() << "\"";
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    
    SortMode sortMode = SORT_BY_BW;
    if (argc > 1 && std::string(argv[1]) == "res") {
        sortMode = SORT_BY_RES;
    }

    const std::string url = "https://lw.bamgrid.com/2.0/hls/vod/bam/ms02/hls/dplus/bao/master_unenc_hdr10_all.m3u8";
    std::string playlistContent = fetchM3U8(url);
    if (playlistContent.empty()) {
        std::cerr << "Failed to fetch playlist." << std::endl;
        return 1;
    }

    // Grouped data
    std::map<std::string, std::vector<std::shared_ptr<MediaItem>>> mediaByGroupId;
    std::map<std::string, std::vector<std::shared_ptr<StreamItem>>> streamsByAudioGroup;

    parseAndGroupStreams(playlistContent, mediaByGroupId, streamsByAudioGroup);

    for (auto& [groupId, streams] : streamsByAudioGroup) {
        if (sortMode == SORT_BY_BW) {
            sortStreamsByBandwidth(streams);
        } else {
            sortStreamsByResolution(streams);
        }
    }

    printSortedStreamsForEachGroup(mediaByGroupId, streamsByAudioGroup);

    return 0;
}
