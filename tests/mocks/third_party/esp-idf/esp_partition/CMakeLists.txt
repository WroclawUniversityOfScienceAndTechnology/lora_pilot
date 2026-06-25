cmake_minimum_required(VERSION 3.14)
set(INTERNAL_NAME MockEspPartition)

add_library(${INTERNAL_NAME} INTERFACE)

target_include_directories(${INTERNAL_NAME}
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
