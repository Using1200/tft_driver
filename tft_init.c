#include "tft_hal.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void tft_controller_init(uint8_t mode){

    tft_hal_init();

    gpio_set_level(TFT_RES, 0);
    vTaskDelay(pdMS_TO_TICKS(10));

    gpio_set_level(TFT_RES, 1);
    vTaskDelay(pdMS_TO_TICKS(5));

    tft_write_cmd(0x11);
    vTaskDelay(pdMS_TO_TICKS(120));

    tft_write_cmd(0x3a);
    tft_write_data(0x05);


    tft_write_cmd(0x36);
    switch (mode)
    {
    case 0:
        tft_write_data(0x00);
        break;
    case 1:
        tft_write_data(0xA0);
        break;
    case 2:
        tft_write_data(0x60);
        break;
    case 3:
        tft_write_data(0xC0);
        break;
    default:
        tft_write_data(0x00);
        break;
    }

    tft_write_cmd(0x29);
}