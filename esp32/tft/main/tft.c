#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"

#define TAG "SSD1306"

void app_main(void) {
  SSD1306_t dev;
  print_config(&dev);

  ssd_print_title(&dev);
}
