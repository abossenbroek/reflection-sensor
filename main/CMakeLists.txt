idf_component_register(SRCS  "main.c"
                    PRIV_REQUIRES esp_wifi nvs_flash spi_flash esp_partition  esp-tls esp_http_server esp_timer
                    INCLUDE_DIRS ".")
