/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <drivers/gpio/gpio_sx1509b.h>

#define GREEN_LED 5
#define BLUE_LED 6
#define RED_LED 7

enum sx1509b_color { sx1509b_red = 0, sx1509b_green, sx1509b_blue };

const struct device *sx1509b_dev;
static struct k_delayed_work rgb_work;
static uint8_t which_color = sx1509b_red;
static uint8_t iterator;

static void rgb_work_handler(struct k_work *work)
{
	if (which_color == sx1509b_red) {
		sx1509b_led_intensity_pin_set(sx1509b_dev, RED_LED, iterator);

		iterator++;

		if (iterator >= 255) {
			sx1509b_led_intensity_pin_set(sx1509b_dev, RED_LED, 0);
			which_color = sx1509b_green;
			iterator = 0;
		}
	} else if (which_color == sx1509b_green) {
		sx1509b_led_intensity_pin_set(sx1509b_dev, GREEN_LED, iterator);

		iterator++;

		if (iterator >= 255) {
			sx1509b_led_intensity_pin_set(sx1509b_dev, GREEN_LED,
						      0);
			which_color = sx1509b_blue;
			iterator = 0;
		}
	} else if (which_color == sx1509b_blue) {
		sx1509b_led_intensity_pin_set(sx1509b_dev, BLUE_LED, iterator);

		iterator++;

		if (iterator >= 255) {
			sx1509b_led_intensity_pin_set(sx1509b_dev, BLUE_LED, 0);
			which_color = sx1509b_red;
			iterator = 0;
		}
	}

	k_delayed_work_submit(&rgb_work, K_MSEC(10));
}

void main(void)
{
	int err;

	printk("SX1509B intensity sample\n");

	sx1509b_dev = device_get_binding(DT_PROP(DT_NODELABEL(sx1509b), label));

	if (sx1509b_dev == NULL) {
		printk("Error binding SX1509B device\n");

		return;
	}

	for (int i = GREEN_LED; i <= RED_LED; i++) {
		err = sx1509b_led_intensity_pin_configure(sx1509b_dev, i);

		if (err) {
			printk("Error configuring pin for LED intensity\n");
		}
	}

	k_delayed_work_init(&rgb_work, rgb_work_handler);
	k_delayed_work_submit(&rgb_work, K_NO_WAIT);
}
