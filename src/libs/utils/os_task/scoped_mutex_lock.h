/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

namespace utils
{
class ScopedMutexLock
{
public:
    explicit ScopedMutexLock(SemaphoreHandle_t mutex, TickType_t timeout = portMAX_DELAY) :
      mutex_(mutex), locked_(xSemaphoreTakeRecursive(mutex_, timeout) == pdTRUE)
    {
    }

    ~ScopedMutexLock()
    {
        if (locked_)
        {
            xSemaphoreGiveRecursive(mutex_);
        }
    }

    ScopedMutexLock(ScopedMutexLock const&) = delete;
    ScopedMutexLock& operator=(ScopedMutexLock const&) = delete;
    ScopedMutexLock(ScopedMutexLock&&) = delete;
    ScopedMutexLock& operator=(ScopedMutexLock&&) = delete;

    bool isLocked() const
    {
        return locked_;
    }

private:
    SemaphoreHandle_t mutex_;
    bool locked_;
};
}  // namespace utils
