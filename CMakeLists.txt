cmake_minimum_required(VERSION 3.5)
project(fetch_parse_sort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/m3u8-cpp/include
)

find_package(CURL REQUIRED)

add_executable(fetch_parse_sort fetch_parse_sort.cpp)

target_link_libraries(fetch_parse_sort CURL::libcurl)
