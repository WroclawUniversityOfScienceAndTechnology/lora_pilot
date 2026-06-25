/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */
#include "os_task.h"
#include <esp_task_wdt.h>

using namespace utils;

[[maybe_unused]] constexpr unsigned short PLATFORM_WORD_SIZE = 4;

OsTask::OsTask(const char* task_name, size_t stack_size, const uint16_t delay, uint16_t task_priority,
               bool wdt_en) noexcept :
  is_running_(false),
  task_name_(task_name),
  stack_size_(stack_size),
  delay_(delay),
  task_priority_(task_priority),
  task_counter_(0),
  last_wake_time_(0),
  task_handle_(nullptr),
  wdt_enabled_(wdt_en)
{
}

OsTask::~OsTask()
{
    destroy();
}

void OsTask::initializeTaskWatchdog()
{
    // Define the configuration for the Task Watchdog Timer (TWDT)
    esp_task_wdt_config_t wdt_config = {
        .timeout_ms = 30000,                    // Timeout after 30 seconds
        .idle_core_mask = (1 << 0) | (1 << 1),  // Monitor both CPU 0 and CPU 1 idle tasks
        .trigger_panic = true                   // Trigger a panic and reset if the watchdog times out
    };

    // Deinitialize the Task Watchdog Timer if it's already initialized
    esp_task_wdt_deinit();

    // Initialize the Task Watchdog Timer with the given configuration
    esp_task_wdt_init(&wdt_config);
}

void OsTask::run()
{
    if (is_running_)
    {
        // is running already then try to resume
        vTaskResume(task_handle_);
        return;
    }

    is_running_ = true;
    BaseType_t task_returned =
        xTaskCreatePinnedToCore(runLoop, task_name_, stack_size_, this, task_priority_, &task_handle_, 1);

    if (task_returned != pdPASS)
    {
        is_running_ = false;
    }
}

void OsTask::join()
{
    if (task_handle_ == nullptr)
    {
        return;
    }

    is_running_ = false;

    while (task_handle_ != nullptr)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void OsTask::destroy()
{
    if (task_handle_ != nullptr)
    {
        is_running_ = false;

        if (xTaskGetCurrentTaskHandle() == task_handle_)
        {
            // Self-deletion: safely delete the task
            vTaskDelay(pdMS_TO_TICKS(10));
            vTaskDelete(nullptr);
            return;
        }

        esp_task_wdt_delete(task_handle_);

        vTaskSuspend(task_handle_);
        vTaskDelete(task_handle_);
        task_handle_ = nullptr;
    }
}

uint16_t OsTask::getDelay()
{
    return delay_;
}

void OsTask::setDelay(uint16_t delay)
{
    delay_ = delay;
}

uint32_t OsTask::getTaskCounter()
{
    return task_counter_;
}

void OsTask::resetTaskCounter()
{
    task_counter_ = 0;
}

void OsTask::delay(uint32_t delay_ms)
{
    vTaskDelay(pdMS_TO_TICKS(delay_ms));
}

void OsTask::delayTick(uint32_t delay_tick)
{
    vTaskDelay(delay_tick);
}

void OsTask::runLoop(void* parameters)
{
    auto p_this = static_cast<OsTask*>(parameters);
    p_this->last_wake_time_ = xTaskGetTickCount();

    if (p_this->wdt_enabled_)
    {
        esp_task_wdt_add(p_this->task_handle_);
    }
    // Main task loop with watchdog reset
    while (p_this->is_running_)
    {
        p_this->runImplementation();  // Task-specific logic
        p_this->task_counter_ += p_this->delay_;
        // Reset the task's watchdog timer
        if (p_this->wdt_enabled_)
        {
            esp_task_wdt_reset();
        }

        if (!p_this->is_running_)
        {
            break;
        }
        // Delay until the next loop iteration
        vTaskDelayUntil(&p_this->last_wake_time_, pdMS_TO_TICKS(p_this->delay_));
    }

    if (p_this->wdt_enabled_)
    {
        esp_task_wdt_delete(p_this->task_handle_);
    }

    p_this->task_handle_ = nullptr;
    vTaskDelete(nullptr);
}
