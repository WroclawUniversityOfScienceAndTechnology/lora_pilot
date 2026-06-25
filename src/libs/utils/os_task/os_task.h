/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */
#pragma once

#include <stddef.h>  // NOLINT(modernize-deprecated-headers)
#include <stdint.h>  // NOLINT(modernize-deprecated-headers)

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace utils
{
class OsTask
{
public:
    explicit OsTask(const char* task_name, size_t stack_size = 128, uint16_t delay = 1000, uint16_t task_priority = 1,
                    bool wdt_en = true) noexcept;
    virtual ~OsTask();

    OsTask(OsTask const&) = delete;
    OsTask& operator=(OsTask const&) = delete;
    OsTask(OsTask&&) = delete;
    OsTask& operator=(OsTask&&) = delete;

    virtual bool init() = 0;
    virtual void runImplementation() = 0;

    void join();
    void run();
    void destroy();
    void delay(uint32_t delay_ms);
    void delayTick(uint32_t delay_tick);

    uint16_t getDelay();
    void setDelay(uint16_t delay);

    uint32_t getTaskCounter();
    void resetTaskCounter();
    static void initializeTaskWatchdog();

    TaskHandle_t getTaskHandle() const
    {
        return task_handle_;
    }

    bool isRunning() const
    {
        return is_running_;
    }

private:
    bool is_running_;
    const char* task_name_;
    size_t stack_size_;
    uint16_t delay_;
    uint16_t task_priority_;
    uint32_t task_counter_;
    TickType_t last_wake_time_;
    TaskHandle_t task_handle_;
    bool wdt_enabled_;
    static void runLoop(void* parameters);
};
}  // namespace utils
