cmake_minimum_required(VERSION 3.28)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/Piotr/Desktop/study/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(Project)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)
