project(frm2png)
cmake_minimum_required(VERSION 2.8)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

add_definitions (-std=c++11 -Wall)
aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARY})
