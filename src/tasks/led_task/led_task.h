/**
 * @copyright Copyright (C) 2025 Covitech. All rights reserved.
 */

#pragma once

#include <os_task.h>

#include <stddef.h>  // NOLINT(modernize-deprecated-headers)
#include <stdint.h>  // NOLINT(modernize-deprecated-headers)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
extern "C"
{
#include <driver/gpio.h>
}
#pragma GCC diagnostic pop

namespace tasks
{
class LedTask : public utils::OsTask
{
public:
    static constexpr gpio_num_t DEFAULT_LED_GPIO = GPIO_NUM_2;

    explicit LedTask(gpio_num_t led_gpio = DEFAULT_LED_GPIO, bool active_low = false) noexcept;
    bool init() override;
    void runImplementation() override;

private:
    static constexpr uint16_t BLINK_INTERVAL_MS = 2500;
    static constexpr size_t STACK_SIZE = 2048;
    static constexpr uint16_t TASK_PRIORITY = 1;

    gpio_num_t led_gpio_;
    bool active_low_;
    bool led_state_;

    void setLedState(bool enabled);
};

}  // namespace tasks
