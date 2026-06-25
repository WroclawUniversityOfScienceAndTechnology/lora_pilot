/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */

#pragma once

#include <gmock/gmock.h>
#include <static_mock.h>

#include "esp_ota_ops.h"

class MockEspOtaOps : public StaticMock<MockEspOtaOps>
{
public:
    MOCK_METHOD(const esp_partition_t*, esp_ota_get_next_update_partition, (const esp_partition_t* start_from), ());
    MOCK_METHOD(esp_err_t, esp_ota_begin,
                (const esp_partition_t* partition, size_t image_size, esp_ota_handle_t* out_handle), ());
    MOCK_METHOD(esp_err_t, esp_ota_abort, (esp_ota_handle_t handle), ());
    MOCK_METHOD(esp_err_t, esp_ota_write, (esp_ota_handle_t handle, const void* data, size_t size), ());
    MOCK_METHOD(esp_err_t, esp_ota_end, (esp_ota_handle_t handle), ());
    MOCK_METHOD(esp_err_t, esp_ota_set_boot_partition, (const esp_partition_t* partition), ());
    MOCK_METHOD((const esp_app_desc_t*), esp_app_get_description, (), ());

};
