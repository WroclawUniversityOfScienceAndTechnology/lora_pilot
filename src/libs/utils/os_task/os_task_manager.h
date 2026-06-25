/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */

#pragma once

#include "os_task.h"

#include <stddef.h>  // NOLINT(modernize-deprecated-headers)

namespace utils
{
class OsTaskManager
{
public:
    OsTaskManager();
    ~OsTaskManager() = default;

    OsTaskManager(OsTaskManager const&) = delete;
    OsTaskManager& operator=(OsTaskManager const&) = delete;
    OsTaskManager(OsTaskManager&&) = delete;
    OsTaskManager& operator=(OsTaskManager&&) = delete;

    // Add a task to the manager
    bool addTask(OsTask& task);

    // Start all tasks managed by the manager
    void startAll();

    // Stop all tasks managed by the manager
    void stopAll();

    // Get the number of tasks
    size_t getTaskCount() const;

private:
    static constexpr size_t MAX_TASKS = 8;

    size_t task_count_;
    OsTask* tasks_[MAX_TASKS];  // NOLINT(modernize-avoid-c-arrays)
};
}  // namespace utils
