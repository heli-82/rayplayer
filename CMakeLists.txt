cmake_minimum_required(VERSION 3.20)
project(ray)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(raylib)
find_package(TagLib REQUIRED)
add_executable(ray main.cpp)
add_subdirectory(nativefiledialog-extended)
target_link_libraries(ray PRIVATE raylib)
target_link_libraries(ray PRIVATE nfd)
target_link_libraries(ray PRIVATE TagLib::tag)
