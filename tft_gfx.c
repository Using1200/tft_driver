#include "tft_gfx.h"
#include "tft_hal.h"
#include "esp_log.h"
#include "font8x8_basic.h"
#include "esp_heap_caps.h"

void tft_set_window(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1){

    tft_write_cmd(0x2A);
    tft_write_data(x0 >> 8);
    tft_write_data(x0 & 0xFF);
    tft_write_data(x1 >> 8);
    tft_write_data(x1 & 0xFF);

    tft_write_cmd(0x2B);
    tft_write_data(y0 >> 8);
    tft_write_data(y0 &  0xFF);
    tft_write_data(y1 >> 8);
    tft_write_data(y1 &  0xFF);

    tft_write_cmd(0x2C);
}

void tft_draw_pixel(uint16_t x, uint16_t y, uint16_t color){

    tft_set_window(x,y,x,y);

    // Une couleur est codée sur 16 bits (2 octets), tandis que la fonction
    // tft_write_data() transmet un seul octet (8 bits) à chaque appel.
    tft_write_data(color >> 8);    // Octet de poids fort (MSB)
    tft_write_data(color & 0xFF);  // Octet de poids faible (LSB)

}

void tft_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){

    uint16_t x1 = x + w - 1;
    uint16_t y1 = y + h - 1;
    uint32_t total = w * h;

    tft_set_window(x, y, x1, y1);

    for (uint32_t i = 0; i < total; i++){

        tft_write_data(color >> 8);
        tft_write_data(color & 0xFF);
    }
    
}

void tft_fill_rect_dma(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color){

    uint16_t x1 = x + w - 1;
    uint16_t y1 = y + h - 1;

    uint32_t total = w * h;
    uint32_t total_bytes = total * 2;
    uint32_t transactions = total_bytes / TFT_DMA_BUFFER_SIZE; // trouver le nombre de transaction de BUFFER_SIZE octets
    uint32_t reste = total_bytes % TFT_DMA_BUFFER_SIZE;   // reste inferieur a BUFFER_SIZE

    tft_set_window(x, y, x1, y1);

    void* buffer = heap_caps_malloc(TFT_DMA_BUFFER_SIZE, MALLOC_CAP_DMA); // Allouer la memoire pour qu'elle soir accessible par DMA

    if (buffer == NULL) {
        ESP_LOGE("TFT", "DMA malloc failed");
        return;
    }


    uint8_t *buf = (uint8_t *)buffer;  // acceder octet pat octet 

    for (int i = 0; i < TFT_DMA_BUFFER_SIZE; i += 2) {
        buf[i]     = color >> 8;
        buf[i + 1] = color & 0xFF;
    }

    for (int i = 0; i < transactions; i++)
    {
        tft_write_buffer(buffer, TFT_DMA_BUFFER_SIZE);
    }

    if (reste > 0)
    {
        tft_write_buffer(buffer, reste); // transfert du reste inferieur a BUFFER_SIZE
    }
    

    heap_caps_free(buffer);
    
}

void tft_fill_screen(uint16_t color){

    tft_fill_rect(0, 0, TFT_WIDTH, TFT_HEIGHT, color);
}


void tft_draw_char(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg){

    //Un caaractère fait 8 pixels sur 8 pixels réprésenter par 8*8 bits 

    uint8_t bit;

    for (uint8_t i = 0; i < 8; i++) // i pour la ligne
    {
        for (int8_t j = 0; j < 8; j++)  // j pour la colonne
        {
            bit = (font8x8_basic[(unsigned char)c][i] >> j) & 1;  // bit contient le pixel de la ligne i et la colonne j

            tft_draw_pixel(x + j, y + i, bit ? color : bg); // bit == 0 --> bg , bit == 1 --> color 
        }
    }
}

void tft_draw_string(uint16_t x, uint16_t y, const char *str, uint16_t color, uint16_t bg){

    const char *p = str;

    while(*p != '\0'){
        tft_draw_char(x, y, *p++, color, bg);
        x += 8;
    }

}

void tft_set_mode(uint8_t mode){

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
}
