/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_GPIO_GPIO_SX1509B_H_
#define ZEPHYR_INCLUDE_DRIVERS_GPIO_GPIO_SX1509B_H_

int sx1509b_pwm_pin_configure(struct device *dev, gpio_pin_t pin);

int sx1509b_pwm_pin_set(struct device *dev, gpio_pin_t pin, uint8_t pwm_value);

#endif /* ZEPHYR_INCLUDE_DRIVERS_GPIO_GPIO_SX1509B_H_ */
