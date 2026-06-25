idf_component_register(SRCS "lora_pilot.cpp"
                    INCLUDE_DIRS "")

add_subdirectory(libs)
add_subdirectory(tasks)

target_link_libraries(${COMPONENT_TARGET} 
    PRIVATE
        idf::esp_common
        idf::nvs_flash
        tasks::led_task
        utils::os_task
)
