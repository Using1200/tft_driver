#include "tft_hal.h"

#include "driver/spi_master.h"
#include "esp_log.h"





spi_device_handle_t handle_tft_spi;


esp_err_t tft_hal_init(void){

    spi_bus_config_t buscfg = {
        .mosi_io_num = TFT_MOSI,
        .miso_io_num = -1,          // Not use 
        .sclk_io_num = TFT_SCLK,
        .quadwp_io_num = -1,        // Not use
        .quadhd_io_num = -1,         // Not use
        .max_transfer_sz = TFT_DMA_BUFFER_SIZE
    };

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = TFT_FREQUENCY,
        .mode = 0,                              // <- CPOL =0  , CPHA = 0
        .spics_io_num = TFT_CS,
        .queue_size = 1                 // number of pending transactions
    };

    gpio_set_direction(TFT_RES, GPIO_MODE_OUTPUT);
    gpio_set_direction(TFT_BL, GPIO_MODE_OUTPUT);
    gpio_set_direction(TFT_DC, GPIO_MODE_OUTPUT);

    gpio_set_level(TFT_BL, 1);
    gpio_set_level(TFT_RES, 1);


    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &handle_tft_spi));
    

    return ESP_OK;
}

void tft_write_cmd(uint8_t cmd){
    
    gpio_set_level(TFT_DC, 0);

    spi_transaction_t t = {
        .flags = SPI_TRANS_USE_TXDATA,
        .length =8,              
        .tx_data = {cmd, 0, 0, 0},
        .rx_buffer = NULL
    };

    spi_device_transmit(handle_tft_spi, &t);
    
}

void tft_write_data(uint8_t data){

    gpio_set_level(TFT_DC, 1);

    spi_transaction_t t = {
        .flags = SPI_TRANS_USE_TXDATA,
        .length = 8,
        .tx_data = {data, 0, 0, 0},
        .rx_buffer = NULL
    };

    spi_device_transmit(handle_tft_spi, &t);
}

void tft_write_buffer(void *buffer, size_t len_bytes){

    gpio_set_level(TFT_DC, 1);

    spi_transaction_t t = {
        .length = 8 * len_bytes,
        .tx_buffer = buffer,
        .rx_buffer = NULL
    };

    spi_device_transmit(handle_tft_spi, &t);
}