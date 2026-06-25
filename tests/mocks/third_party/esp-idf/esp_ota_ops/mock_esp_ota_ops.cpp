/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */
#include "mock_esp_ota_ops.h"

const esp_partition_t* esp_ota_get_next_update_partition(const esp_partition_t* start_from)
{
    return MockEspOtaOps::instance().esp_ota_get_next_update_partition(start_from);
}

esp_err_t esp_ota_begin(const esp_partition_t* partition, size_t image_size, esp_ota_handle_t* out_handle)
{
    return MockEspOtaOps::instance().esp_ota_begin(partition, image_size, out_handle);
}

esp_err_t esp_ota_abort(esp_ota_handle_t handle)
{
    return MockEspOtaOps::instance().esp_ota_abort(handle);
}

esp_err_t esp_ota_write(esp_ota_handle_t handle, const void* data, size_t size)
{
    return MockEspOtaOps::instance().esp_ota_write(handle, data, size);
}

esp_err_t esp_ota_end(esp_ota_handle_t handle)
{
    return MockEspOtaOps::instance().esp_ota_end(handle);
}

esp_err_t esp_ota_set_boot_partition(const esp_partition_t* partition)
{
    return MockEspOtaOps::instance().esp_ota_set_boot_partition(partition);
}

const esp_app_desc_t* esp_app_get_description() {
    static esp_app_desc_t mock_desc = {
        .version = "v1.0.0-mock",
        .project_name = "ucd_base",
        .time = "12:00:00",
        .date = "2025-05-14",
        .idf_ver = "IDF-mock"
    };
    
    return &mock_desc;
}