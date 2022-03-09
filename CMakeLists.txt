cmake_minimum_required(VERSION 3.16)
project(Task_32_2_JSON)

set(JSON_BuildTests OFF CACHE INTERNAL " ")
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(nlohmann_json)
add_executable(Task_32_2_JSON main.cpp)

target_link_libraries(Task_32_2_JSON PRIVATE nlohmann_json::nlohmann_json)