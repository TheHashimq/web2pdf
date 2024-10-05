cmake_minimum_required(VERSION 3.20)
project(Web2Pdf)

set(CMAKE_CXX_STANDARD 20)

# to include the include/ directory
include_directories(include)

# required packages 
find_package(CURL REQUIRED)


add_executable(web2pdf src/main.cpp src/htmlParser.cpp)
target_link_libraries(web2pdf ${CURL_LIBRARIES})


