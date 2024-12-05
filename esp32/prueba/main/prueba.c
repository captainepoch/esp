#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/gpio_types.h"
#include "portmacro.h"
#include <stdio.h>

#define BLINK_GPIO 2
#define TAG "LED"

// LED state
uint8_t s_led_state = 0;

void setup_board_led() {
  ESP_LOGI(TAG, "Example configured to blink GPIO LED!");

  gpio_reset_pin(BLINK_GPIO);
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

  ESP_LOGI(TAG, "GPIO PORTS SETUP!");
}

void blink_led() {
  s_led_state = !s_led_state;
  ESP_LOGI(TAG, "LED STATE: %d", s_led_state);

  gpio_set_level(BLINK_GPIO, s_led_state);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void app_main(void) {
  setup_board_led();

  while (1) {
    blink_led();
  }
}
