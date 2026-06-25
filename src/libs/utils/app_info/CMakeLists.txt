cmake_minimum_required(VERSION 3.14)
set(INTERNAL_NAME app_info)

add_library(${INTERNAL_NAME} 
    STATIC 
        app_info.cpp
)
add_library(utils::${INTERNAL_NAME} ALIAS ${INTERNAL_NAME})

target_link_libraries(${INTERNAL_NAME}
    PRIVATE
        idf::app_update
)
target_include_directories(${INTERNAL_NAME} 
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
