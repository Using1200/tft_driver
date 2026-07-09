#pragma once

#include "tft_gfx.h"
#include "tft_hal.h"


/**
 * @brief Initialisation de l'ecran
 *
 * Permet de :
 *      -lancer la sequance d'allumage.
 *      -choisir le mode.
 *
 * @param mode
 *        - TFT_MODE_DEFAULT
 *        - TFT_MODE_1
 *        - TFT_MODE_2
 *        - TFT_MODE_3
 */
void tft_controller_init(uint8_t mode);
