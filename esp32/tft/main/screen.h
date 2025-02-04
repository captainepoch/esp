#include "ssd1306.h"
#include "logging.h"

#define MAX_LINE_SIZE 16

void print_config(SSD1306_t *dev) {
#if CONFIG_I2C_INTERFACE
  ESP_LOGI(TAG, "INTERFACE is i2c");
  ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d", CONFIG_SDA_GPIO);
  ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d", CONFIG_SCL_GPIO);
  ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);
  i2c_master_init(dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
  ESP_LOGI(TAG, "INTERFACE is SPI");
  ESP_LOGI(TAG, "CONFIG_MOSI_GPIO=%d", CONFIG_MOSI_GPIO);
  ESP_LOGI(TAG, "CONFIG_SCLK_GPIO=%d", CONFIG_SCLK_GPIO);
  ESP_LOGI(TAG, "CONFIG_CS_GPIO=%d", CONFIG_CS_GPIO);
  ESP_LOGI(TAG, "CONFIG_DC_GPIO=%d", CONFIG_DC_GPIO);
  ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);
  spi_master_init(dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO,
                  CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_SSD1306_128x64
  ESP_LOGI(TAG, "Panel is 128x64");
  ssd1306_init(dev, 128, 64);
#endif // CONFIG_SSD1306_128x64
       //
#if CONFIG_SSD1306_128x32
  ESP_LOGE(TAG, "Panel is 128x32. This demo cannot be run.");
  while (1) {
    vTaskDelay(1);
  }
#endif // CONFIG_SSD1306_128x32

  ssd1306_clear_screen(dev, false);
  ssd1306_contrast(dev, 0xff);
}

void ssd_print_title(SSD1306_t *dev) {
	ssd1306_display_text(dev, 0, "Hola Nacho", 11, false);
}
