#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <curl/curl.h>
#include "m3u8-cpp/include/m3u8/Parser.h"

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

void printGroupedStreamsByAudio(
    const std::map<std::string, std::vector<std::shared_ptr<MediaItem>>>& mediaByGroupId,
    const std::map<std::string, std::vector<std::shared_ptr<StreamItem>>>& streamsByAudioGroup)
{
    std::cout << "\n====== GROUPED STREAMS BY AUDIO ======\n";

    for (const auto& [groupId, streams] : streamsByAudioGroup) {
        std::cout << "\n=== AUDIO GROUP: " << groupId << " ===\n";

        if (mediaByGroupId.count(groupId)) {
            for (const auto& media : mediaByGroupId.at(groupId)) {
                auto& attr = media->attributeList;  // ⚡ no const here

                std::cout << "MEDIA: NAME=" << attr.get("NAME")
                          << ", URI=" << attr.get("URI")
                          << ", CHANNELS=" << attr.get("CHANNELS")
                          << ", LANGUAGE=" << attr.get("LANGUAGE") << "\n";
            }
        }

        for (const auto& stream : streams) {
            auto& attr = stream->attributeList;  // ⚡ no const here

            std::cout << "  STREAM: BW=" << attr.get("BANDWIDTH")
                      << ", RES=" << attr.get("RESOLUTION")
                      << ", CODECS=" << attr.get("CODECS")
                      << ", URI=" << stream->get("uri") << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
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

    // Output the result
    printGroupedStreamsByAudio(mediaByGroupId, streamsByAudioGroup);

    return 0;
}
