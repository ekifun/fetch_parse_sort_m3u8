# fetch_parse_sort_m3u8

To fetch, parse, group, and sort an HLS playlist in C++, you can utilize the m3u8-cpp library, a header-only C++ library designed for parsing M3U8 playlists. ​
Step 1: Set Up the Dependencies
Ensure you have the necessary dependencies installed:​

On macOS, follow the following steps to install the dependencies:
    1. Install Homebrew (if not already installed)
Open Terminal and paste:
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

    2. Install dependencies via Homebrew
brew install nlohmann-json curl cmake

On Linux, follow the following steps to install the dependencies:
Ensure you have the necessary dependencies installed:​Lib.rs+1GitHub+1
sudo apt install nlohmann-json3-dev libcurl4-openssl-dev

Step 2: Download  and Build m3u8-cpp Library
Under fetch_parse_sort_m3u8 directory, clone the m3u8-cpp repository and build the project:
git clone https://github.com/zeerd/m3u8-cpp.git
cd m3u8-cpp
mkdir build && cd build
Replace CMakeLists.txt with CMakeLists-m3u8-cpp.txt and rename it to CMakeLists.txt
cmake .. && make -j && sudo make install

Step 3: Build fetch_parse_sort.cpp
Under fetch_parse_sort_m3u8 directory, 
mkdir build && cd build
cmake .. && make -j && sudo make install

Step 4: Run fetch_parse_sort

4.1 To fetch, parse, group, and sort an HLS playlist according to bandwidth
./fetch_parse_sort bw

====== GROUPED STREAMS BY AUDIO ======
=== AUDIO GROUP: aac-128k ===
MEDIA: NAME="English", URI="audio/unenc/aac_128k/vod.m3u8", CHANNELS="2", LANGUAGE="en"
  STREAM: BW=25702333, RES=3840x2160, CODECS="mp4a.40.2,hvc1.2.4.H150.90", URI="hdr10/unenc/16500k/vod.m3u8"
  STREAM: BW=20655057, RES=3840x2160, CODECS="mp4a.40.2,hvc1.2.4.H150.90", URI="hdr10/unenc/13000k/vod.m3u8"
  STREAM: BW=15811232, RES=2560x1440, CODECS="mp4a.40.2,hvc1.2.4.L150.90", URI="hdr10/unenc/10000k/vod.m3u8"
  STREAM: BW=13911387, RES=2560x1440, CODECS="mp4a.40.2,hvc1.2.4.L150.90", URI="hdr10/unenc/8800k/vod.m3u8"
  STREAM: BW=12156778, RES=1920x1080, CODECS="mp4a.40.2,hvc1.2.4.H120.90", URI="hdr10/unenc/7700k/vod.m3u8"
  STREAM: BW=9533270, RES=1920x1080, CODECS="mp4a.40.2,hvc1.2.4.L120.90", URI="hdr10/unenc/6000k/vod.m3u8"
  STREAM: BW=6986073, RES=1920x1080, CODECS="mp4a.40.2,hvc1.2.4.L120.90", URI="hdr10/unenc/4600k/vod.m3u8"
  STREAM: BW=5044473, RES=1280x720, CODECS="mp4a.40.2,hvc1.2.4.L93.90", URI="hdr10/unenc/3300k/vod.m3u8"
  STREAM: BW=3790212, RES=1280x720, CODECS="mp4a.40.2,hvc1.2.4.L93.90", URI="hdr10/unenc/2500k/vod.m3u8"
  STREAM: BW=2483789, RES=960x540, CODECS="mp4a.40.2,hvc1.2.4.L90.90", URI="hdr10/unenc/1650k/vod.m3u8"
=== AUDIO GROUP: aac-64k ===
MEDIA: NAME="English", URI="audio/unenc/aac_64k/vod.m3u8", CHANNELS="2", LANGUAGE="en"
  STREAM: BW=1352519, RES=640x360, CODECS="mp4a.40.2,hvc1.2.4.L63.90", URI="hdr10/unenc/900k/vod.m3u8"
  STREAM: BW=705826, RES=640x360, CODECS="mp4a.40.2,hvc1.2.4.L63.90", URI="hdr10/unenc/450k/vod.m3u8"
=== AUDIO GROUP: atmos ===
MEDIA: NAME="English", URI="audio/unenc/atmos_1024k/vod.m3u8", CHANNELS="16/JOC", LANGUAGE="en"
  STREAM: BW=26598940, RES=3840x2160, CODECS="ec-3,hvc1.2.4.H150.90", URI="hdr10/unenc/16500k/vod.m3u8"
  STREAM: BW=21551664, RES=3840x2160, CODECS="ec-3,hvc1.2.4.H150.90", URI="hdr10/unenc/13000k/vod.m3u8"
  STREAM: BW=16707839, RES=2560x1440, CODECS="ec-3,hvc1.2.4.L150.90", URI="hdr10/unenc/10000k/vod.m3u8"
  STREAM: BW=14807994, RES=2560x1440, CODECS="ec-3,hvc1.2.4.L150.90", URI="hdr10/unenc/8800k/vod.m3u8"
  STREAM: BW=13053385, RES=1920x1080, CODECS="ec-3,hvc1.2.4.H120.90", URI="hdr10/unenc/7700k/vod.m3u8"
  STREAM: BW=10429877, RES=1920x1080, CODECS="ec-3,hvc1.2.4.L120.90", URI="hdr10/unenc/6000k/vod.m3u8"
  STREAM: BW=7882680, RES=1920x1080, CODECS="ec-3,hvc1.2.4.L120.90", URI="hdr10/unenc/4600k/vod.m3u8"
  STREAM: BW=5941080, RES=1280x720, CODECS="ec-3,hvc1.2.4.L93.90", URI="hdr10/unenc/3300k/vod.m3u8"
  STREAM: BW=4686819, RES=1280x720, CODECS="ec-3,hvc1.2.4.L93.90", URI="hdr10/unenc/2500k/vod.m3u8"
  STREAM: BW=3380396, RES=960x540, CODECS="ec-3,hvc1.2.4.L90.90", URI="hdr10/unenc/1650k/vod.m3u8"
  STREAM: BW=2312764, RES=640x360, CODECS="ec-3,hvc1.2.4.L63.90", URI="hdr10/unenc/900k/vod.m3u8"
  STREAM: BW=1666071, RES=640x360, CODECS="ec-3,hvc1.2.4.L63.90", URI="hdr10/unenc/450k/vod.m3u8"
=== AUDIO GROUP: eac3 ===
MEDIA: NAME="English", URI="audio/unenc/ec3_256k/vod.m3u8", CHANNELS="6", LANGUAGE="en"
  STREAM: BW=25830920, RES=3840x2160, CODECS="ec-3,hvc1.2.4.H150.90", URI="hdr10/unenc/16500k/vod.m3u8"
  STREAM: BW=20783644, RES=3840x2160, CODECS="ec-3,hvc1.2.4.H150.90", URI="hdr10/unenc/13000k/vod.m3u8"
  STREAM: BW=15939819, RES=2560x1440, CODECS="ec-3,hvc1.2.4.L150.90", URI="hdr10/unenc/10000k/vod.m3u8"
  STREAM: BW=14039974, RES=2560x1440, CODECS="ec-3,hvc1.2.4.L150.90", URI="hdr10/unenc/8800k/vod.m3u8"
  STREAM: BW=12285365, RES=1920x1080, CODECS="ec-3,hvc1.2.4.H120.90", URI="hdr10/unenc/7700k/vod.m3u8"
  STREAM: BW=9661857, RES=1920x1080, CODECS="ec-3,hvc1.2.4.L120.90", URI="hdr10/unenc/6000k/vod.m3u8"
  STREAM: BW=7114660, RES=1920x1080, CODECS="ec-3,hvc1.2.4.L120.90", URI="hdr10/unenc/4600k/vod.m3u8"
  STREAM: BW=5173060, RES=1280x720, CODECS="ec-3,hvc1.2.4.L93.90", URI="hdr10/unenc/3300k/vod.m3u8"
  STREAM: BW=3918799, RES=1280x720, CODECS="ec-3,hvc1.2.4.L93.90", URI="hdr10/unenc/2500k/vod.m3u8"
  STREAM: BW=2612376, RES=960x540, CODECS="ec-3,hvc1.2.4.L90.90", URI="hdr10/unenc/1650k/vod.m3u8"
  STREAM: BW=1544744, RES=640x360, CODECS="ec-3,hvc1.2.4.L63.90", URI="hdr10/unenc/900k/vod.m3u8"
  STREAM: BW=898051, RES=640x360, CODECS="ec-3,hvc1.2.4.L63.90", URI="hdr10/unenc/450k/vod.m3u8"

4.2 To fetch, parse, group, and sort an HLS playlist according to resolution
./fetch_parse_sort res

====== GROUPED STREAMS BY AUDIO ======
=== AUDIO GROUP: aac-128k ===
MEDIA: NAME="English", URI="audio/unenc/aac_128k/vod.m3u8", CHANNELS="2", LANGUAGE="en"
  STREAM: BW=25702333, RES=3840x2160, CODECS="mp4a.40.2,hvc1.2.4.H150.90", URI="hdr10/unenc/16500k/vod.m3u8"
  STREAM: BW=20655057, RES=3840x2160, CODECS="mp4a.40.2,hvc1.2.4.H150.90", URI="hdr10/unenc/13000k/vod.m3u8"
  STREAM: BW=15811232, RES=2560x1440, CODECS="mp4a.40.2,hvc1.2.4.L150.90", URI="hdr10/unenc/10000k/vod.m3u8"
  STREAM: BW=13911387, RES=2560x1440, CODECS="mp4a.40.2,hvc1.2.4.L150.90", URI="hdr10/unenc/8800k/vod.m3u8"
  STREAM: BW=12156778, RES=1920x1080, CODECS="mp4a.40.2,hvc1.2.4.H120.90", URI="hdr10/unenc/7700k/vod.m3u8"
  STREAM: BW=9533270, RES=1920x1080, CODECS="mp4a.40.2,hvc1.2.4.L120.90", URI="hdr10/unenc/6000k/vod.m3u8"
  STREAM: BW=6986073, RES=1920x1080, CODECS="mp4a.40.2,hvc1.2.4.L120.90", URI="hdr10/unenc/4600k/vod.m3u8"
  STREAM: BW=5044473, RES=1280x720, CODECS="mp4a.40.2,hvc1.2.4.L93.90", URI="hdr10/unenc/3300k/vod.m3u8"
  STREAM: BW=3790212, RES=1280x720, CODECS="mp4a.40.2,hvc1.2.4.L93.90", URI="hdr10/unenc/2500k/vod.m3u8"
  STREAM: BW=2483789, RES=960x540, CODECS="mp4a.40.2,hvc1.2.4.L90.90", URI="hdr10/unenc/1650k/vod.m3u8"
=== AUDIO GROUP: aac-64k ===
MEDIA: NAME="English", URI="audio/unenc/aac_64k/vod.m3u8", CHANNELS="2", LANGUAGE="en"
  STREAM: BW=705826, RES=640x360, CODECS="mp4a.40.2,hvc1.2.4.L63.90", URI="hdr10/unenc/450k/vod.m3u8"
  STREAM: BW=1352519, RES=640x360, CODECS="mp4a.40.2,hvc1.2.4.L63.90", URI="hdr10/unenc/900k/vod.m3u8"
=== AUDIO GROUP: atmos ===
MEDIA: NAME="English", URI="audio/unenc/atmos_1024k/vod.m3u8", CHANNELS="16/JOC", LANGUAGE="en"
  STREAM: BW=21551664, RES=3840x2160, CODECS="ec-3,hvc1.2.4.H150.90", URI="hdr10/unenc/13000k/vod.m3u8"
  STREAM: BW=26598940, RES=3840x2160, CODECS="ec-3,hvc1.2.4.H150.90", URI="hdr10/unenc/16500k/vod.m3u8"
  STREAM: BW=14807994, RES=2560x1440, CODECS="ec-3,hvc1.2.4.L150.90", URI="hdr10/unenc/8800k/vod.m3u8"
  STREAM: BW=16707839, RES=2560x1440, CODECS="ec-3,hvc1.2.4.L150.90", URI="hdr10/unenc/10000k/vod.m3u8"
  STREAM: BW=13053385, RES=1920x1080, CODECS="ec-3,hvc1.2.4.H120.90", URI="hdr10/unenc/7700k/vod.m3u8"
  STREAM: BW=7882680, RES=1920x1080, CODECS="ec-3,hvc1.2.4.L120.90", URI="hdr10/unenc/4600k/vod.m3u8"
  STREAM: BW=10429877, RES=1920x1080, CODECS="ec-3,hvc1.2.4.L120.90", URI="hdr10/unenc/6000k/vod.m3u8"
  STREAM: BW=5941080, RES=1280x720, CODECS="ec-3,hvc1.2.4.L93.90", URI="hdr10/unenc/3300k/vod.m3u8"
  STREAM: BW=4686819, RES=1280x720, CODECS="ec-3,hvc1.2.4.L93.90", URI="hdr10/unenc/2500k/vod.m3u8"
  STREAM: BW=3380396, RES=960x540, CODECS="ec-3,hvc1.2.4.L90.90", URI="hdr10/unenc/1650k/vod.m3u8"
  STREAM: BW=1666071, RES=640x360, CODECS="ec-3,hvc1.2.4.L63.90", URI="hdr10/unenc/450k/vod.m3u8"
  STREAM: BW=2312764, RES=640x360, CODECS="ec-3,hvc1.2.4.L63.90", URI="hdr10/unenc/900k/vod.m3u8"
=== AUDIO GROUP: eac3 ===
MEDIA: NAME="English", URI="audio/unenc/ec3_256k/vod.m3u8", CHANNELS="6", LANGUAGE="en"
  STREAM: BW=20783644, RES=3840x2160, CODECS="ec-3,hvc1.2.4.H150.90", URI="hdr10/unenc/13000k/vod.m3u8"
  STREAM: BW=25830920, RES=3840x2160, CODECS="ec-3,hvc1.2.4.H150.90", URI="hdr10/unenc/16500k/vod.m3u8"
  STREAM: BW=14039974, RES=2560x1440, CODECS="ec-3,hvc1.2.4.L150.90", URI="hdr10/unenc/8800k/vod.m3u8"
  STREAM: BW=15939819, RES=2560x1440, CODECS="ec-3,hvc1.2.4.L150.90", URI="hdr10/unenc/10000k/vod.m3u8"
  STREAM: BW=12285365, RES=1920x1080, CODECS="ec-3,hvc1.2.4.H120.90", URI="hdr10/unenc/7700k/vod.m3u8"
  STREAM: BW=7114660, RES=1920x1080, CODECS="ec-3,hvc1.2.4.L120.90", URI="hdr10/unenc/4600k/vod.m3u8"
  STREAM: BW=9661857, RES=1920x1080, CODECS="ec-3,hvc1.2.4.L120.90", URI="hdr10/unenc/6000k/vod.m3u8"
  STREAM: BW=5173060, RES=1280x720, CODECS="ec-3,hvc1.2.4.L93.90", URI="hdr10/unenc/3300k/vod.m3u8"
  STREAM: BW=3918799, RES=1280x720, CODECS="ec-3,hvc1.2.4.L93.90", URI="hdr10/unenc/2500k/vod.m3u8"
  STREAM: BW=2612376, RES=960x540, CODECS="ec-3,hvc1.2.4.L90.90", URI="hdr10/unenc/1650k/vod.m3u8"
  STREAM: BW=898051, RES=640x360, CODECS="ec-3,hvc1.2.4.L63.90", URI="hdr10/unenc/450k/vod.m3u8"
  STREAM: BW=1544744, RES=640x360, CODECS="ec-3,hvc1.2.4.L63.90", URI="hdr10/unenc/900k/vod.m3u8"