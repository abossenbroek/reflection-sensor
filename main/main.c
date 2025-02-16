#include <stdio.h>
#include <inttypes.h>
#include <esp_log.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "take_picture.h"
#include "wifi.h"
#include "diagnostics.h"
#include "http_server.h"

static const char *MAIN_TAG = "MAIN";

void app_main(void)
{
    ESP_LOGI(MAIN_TAG, "Starting main...");
    ESP_LOGI(MAIN_TAG, "Initializing NVS...");
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_LOGI(MAIN_TAG, "NVS initialized");

    print_chip_info();

    wifi_init_sta();

    init_camera();

    start_webserver();

    while (1) {
        ESP_LOGI(MAIN_TAG, "Waiting for incoming connection...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
        


    // for (int i = 10; i >= 0; i--) {
    //     ESP_LOGI(MAIN_TAG, "Restarting in %d seconds...", i);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
    // ESP_LOGI(MAIN_TAG, "Restarting now.");
    // fflush(stdout);
    // esp_restart();
}