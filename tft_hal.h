#pragma once


#include "tft_config.h"
#include "esp_err.h"
#include "driver/gpio.h"


/**
 * @brief Initialise le bus SPI et les GPIO pour le TFT ST7789
 *
 * Configure le bus SPI2, ajoute le device TFT, et initialise
 * les pins DC, RES, BL en sortie avec leurs niveaux par défaut.
 *
 * @return
 *     - ESP_OK           Initialisation réussie
 *     - ESP_ERR_NO_MEM   Echec allocation DMA
 *     - ESP_FAIL         Erreur SPI
 */
esp_err_t tft_hal_init(void);

/**
 * @brief Envoie une commande au contrôleur ST7789
 *
 * Met le pin DC à 0 puis envoie l'octet via SPI.
 *
 * @param cmd  Octet de commande (ex: 0x11 Sleep Out)
 */
void tft_write_cmd(uint8_t cmd);

/**
 * @brief Envoie un octet de donnée au contrôleur ST7789
 *
 * Met le pin DC à 1 puis envoie l'octet via SPI.
 *
 * @param data  Octet de donnée ou paramètre de commande
 */
void tft_write_data(uint8_t data);

/**
 * @brief Envoie un octet de donnée en passant par le DMA au contrôleur ST7789
 *
 * Met le pin DC à 1 puis envoie l'octet via SPI.
 *
 * @param buffer  les octet de donnée envoyer via le DMA
 * @param len_bytes la taille du buffer a envoyer 
 */
void tft_write_buffer(void *buffer, size_t len_bytes);