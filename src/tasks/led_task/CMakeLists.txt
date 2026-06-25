# #
# Copyright (C) 2025 Covitech. All rights reserved.
# #

cmake_minimum_required(VERSION 3.14)
set(INTERNAL_NAME led_task)

add_library(${INTERNAL_NAME}
    STATIC
        led_task.cpp
)

add_library(tasks::${INTERNAL_NAME} ALIAS ${INTERNAL_NAME})

target_link_libraries(${INTERNAL_NAME}
    PUBLIC
        utils::os_task
        idf::driver
        idf::esp_common
)

target_include_directories(${INTERNAL_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
