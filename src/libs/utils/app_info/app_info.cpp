/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */
#include "app_info.h"
#include <esp_ota_ops.h>

using namespace utils;

const char* AppInfo::getVersion()
{
    const esp_app_desc_t* app_description = esp_app_get_description();
    return app_description->version;
}
