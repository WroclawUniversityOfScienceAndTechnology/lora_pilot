# #
# Copyright (C) 2025 Covitech. All rights reserved.
# #

cmake_minimum_required(VERSION 3.14)
set(INTERNAL_NAME os_task)

add_library(${INTERNAL_NAME} 
    STATIC 
        os_task_manager.cpp
        os_task.cpp
)

add_library(utils::${INTERNAL_NAME} ALIAS ${INTERNAL_NAME})

target_link_libraries(${INTERNAL_NAME} 
    PUBLIC
        idf::freertos
        idf::esp_common
)

target_include_directories(${INTERNAL_NAME} 
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
