#pragma once

#define TFT_MOSI    GPIO_NUM_23
#define TFT_SCLK    GPIO_NUM_18
#define TFT_CS      GPIO_NUM_5
#define TFT_DC      GPIO_NUM_2
#define TFT_RES     GPIO_NUM_4
#define TFT_BL      GPIO_NUM_15

#define TFT_WIDTH   240         // largeur de l'ecran
#define TFT_HEIGHT  320         // hauteur de l'ecran

#define TFT_FREQUENCY 15000000

#define TFT_DMA_BUFFER_SIZE 4092 // octet maximun a envoyer a chauqe transction


#define TFT_MODE_DEFAULT 0 // vertical 1 
#define TFT_MODE_1       1 // horizontal 1
#define TFT_MODE_2       2 // vertical 2
#define TFT_MODE_3       3 // horizontal 1