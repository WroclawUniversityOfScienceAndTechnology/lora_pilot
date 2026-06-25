/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */

#include "led_task.h"
#include <esp_log.h>

using namespace tasks;  // NOLINT(readability-identifier-naming)

constexpr char const* const TAG = "LED";

LedTask::LedTask(gpio_num_t led_gpio, bool active_low) noexcept :
  OsTask(TAG, STACK_SIZE, BLINK_INTERVAL_MS, TASK_PRIORITY),
  led_gpio_(led_gpio),
  active_low_(active_low),
  led_state_(false)
{
}

bool LedTask::init()
{
    (void)gpio_reset_pin(led_gpio_);
    (void)gpio_set_direction(led_gpio_, GPIO_MODE_OUTPUT);
    setLedState(false);

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
    ESP_LOGI(TAG, "LED task initialized on GPIO %d", static_cast<int>(led_gpio_));
    return true;
}

void LedTask::runImplementation()
{
    led_state_ = !led_state_;
    setLedState(led_state_);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
    ESP_LOGI(TAG, "Led change state to [%d]", led_state_);
}

void LedTask::setLedState(bool enabled)
{
    const auto gpio_level = static_cast<uint32_t>(active_low_ ? !enabled : enabled);
    (void)gpio_set_level(led_gpio_, gpio_level);
}
