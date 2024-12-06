#include "esp_bt.h"
#include "esp_bt_device.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LOG_TAG "BT_EPOCH"

void bt_gap_start(void);
char *btraddress(uint8_t *addr);

void app_main(void) {
  esp_err_t ret;

  // NVS Init
  ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
      ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

  esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
  if ((ret = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
    ESP_LOGE(LOG_TAG, "%s initialize controller failed: %s", __func__,
             esp_err_to_name(ret));
    return;
  }

  if ((ret = esp_bt_controller_enable(ESP_BT_MODE_BTDM)) != ESP_OK) {
    ESP_LOGE(LOG_TAG, "%s enable controller failed: %s", __func__,
             esp_err_to_name(ret));
    return;
  }

  esp_bluedroid_config_t bluedroid_cfg = BT_BLUEDROID_INIT_CONFIG_DEFAULT();
  if ((ret = esp_bluedroid_init_with_cfg(&bluedroid_cfg)) != ESP_OK) {
    ESP_LOGE(LOG_TAG, "%s initialize bluedroid failed: %s", __func__,
             esp_err_to_name(ret));
    return;
  }

  if ((ret = esp_bluedroid_enable()) != ESP_OK) {
    ESP_LOGE(LOG_TAG, "%s enable bluedroid failed: %s", __func__,
             esp_err_to_name(ret));
    return;
  }

  ESP_LOGI(LOG_TAG, "Own address: [%s]",
           btraddress((uint8_t *)esp_bt_dev_get_address()));

  bt_gap_start();
}

void bt_gap_start(void) {
  // Register GAP callback
  // esp_bt_gap_register_callback(bt_gap_start);

  char *device_name = "BT_EPOCH";
  esp_bt_gap_set_device_name(device_name);

  // Discoverable and connectable mode
  esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
}

char *btraddress(uint8_t *p) {
  if (p == NULL) {
    return NULL;
  }

  char *str = calloc(18, sizeof(char));
  sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x", p[0], p[1], p[2], p[3], p[4],
          p[5]);
  return str;
}
