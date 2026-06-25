/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */
#include "os_task_manager.h"

using namespace utils;  // NOLINT(readability-identifier-naming)

OsTaskManager::OsTaskManager() : task_count_(0), tasks_{}
{
    OsTask::initializeTaskWatchdog();
}

// // Add a task to the manager
bool OsTaskManager::addTask(OsTask& task)
{
    if (task_count_ >= MAX_TASKS)
    {
        return false;
    }

    tasks_[task_count_] = &task;
    ++task_count_;
    return true;
}

// Start all tasks managed by the manager
void OsTaskManager::startAll()
{
    for (size_t index = 0; index < task_count_; ++index)
    {
        auto* task = tasks_[index];
        if ((task != nullptr) && !task->isRunning())
        {
            task->init();
            task->run();
        }
    }
}

// Stop all tasks managed by the manager
void OsTaskManager::stopAll()
{
    for (size_t index = 0; index < task_count_; ++index)
    {
        auto* task = tasks_[index];
        if (task != nullptr)
        {
            task->destroy();
        }
    }
}

// Get the number of tasks managed
size_t OsTaskManager::getTaskCount() const
{
    return task_count_;
}
