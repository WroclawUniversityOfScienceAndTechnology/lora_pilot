/**
 * @copyright Copyright (C) 2025 <Company-Name>. All rights reserved.
 */
#include <os_task.h>
#include <os_task_manager.h>
#include <led_task.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <nvs_flash.h>

#include <esp_log.h>

constexpr char const* const TAG = "MAIN";

extern "C"
{
    void app_main(void);  // NOLINT(readability-identifier-naming): name required by freertos
}

void initNvsFlash()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

/**
 * @brief Main freeRTOS task
 *
 */
void app_main(void)  // NOLINT(readability-identifier-naming): name required by freertos
{
    initNvsFlash();

    utils::OsTaskManager task_manager;

    static tasks::LedTask led_task;
    (void)task_manager.addTask(led_task);

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
    ESP_LOGI(TAG, "Added %zu tasks to the manager", task_manager.getTaskCount());
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
    ESP_LOGI(TAG, "Starting all tasks...");
    task_manager.startAll();

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
