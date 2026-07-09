#pragma once
#include <stdint.h>


/**
 * @brief Defini la zones d'action de notre ecran
 *
 * 0x2A pour definir les colones 
 * 0x2B pour definir les lignes
 *
 * @param x0 le point de depart des colonnes
 * @param y0 le point de depart des lignes
 * @param x1 le point de fin des colonnes
 * @param y1 le point de fin des lignes
 * 
 */
void tft_set_window(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1);

/**
 * @brief Dessine un pixel
 *
 * Dessine a l'intersection de x et y
 *
 * @param x coordonné sur l'axe horizontal
 * @param y coordonné sur l'axe vertical
 * @param color la couleur aplliqué sur le pixel
 * 
 */
void tft_draw_pixel(uint16_t x, uint16_t y, uint16_t color);

/**
 * @brief Remplir un rectangle avec une couleur
 *
 * utilse x, y, w et h pour definir la longueur et largeur du rectangle
 * 
 * @param x le point de depart sur l'axe horizontal
 * @param y le point de depart sur l'axe vertical
 * @param w longueur du rectangle 
 * @param h largeur du rectangle
 * @param color couleur du rectangle
 * 
 */
void tft_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);


/**
 * @brief Remplir un rectangle avec une couleur en passant par le DMA
 *
 * utilse x, y, w et h pour definir la longueur et largeur du rectangle
 * 4095 maximun d'octet envoyer a chauqe transaction 
 * 
 * @param x le point de depart sur l'axe horizontal
 * @param y le point de depart sur l'axe vertical
 * @param w largeur du rectangle 
 * @param h longueur du rectangle
 * @param color couleur du rectangle
 * 
 * @return
 *    - ESP_OK      Succès
 *    - ESP_FAIL    Echec allocation DMA
 */
void tft_fill_rect_dma(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/**
 * @brief Remplir l'ecran avec une couleur
 * 
 * @param color couleur de l'ecran 
 */
void tft_fill_screen(uint16_t color);

/**
 * @brief Dessine un caractère
 *
 * Utilise une lib de police afin de dessiner un caratère
 * 
 * @param x le point de depart sur l'axe horizontal
 * @param y le point de depart sur l'axe vertical
 * @param c caratère a dessiner 
 * @param color couleur du caratere
 * @param bg la couleur de l'arriere plan
 * 
 */
void tft_draw_char(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg);

/**
 * @brief Dessine une chaine caractère
 *
 * Utilise tft_draw_char pour de dessiner plusieurs caratère
 * 
 * @param x le point de depart sur l'axe horizontal
 * @param y le point de depart sur l'axe vertical
 * @param str chaine caratère a dessiner 
 * @param color couleur du caratere
 * @param bg la couleur de l'arriere plan
 * 
 */
void tft_draw_string(uint16_t x, uint16_t y, const char *str, uint16_t color, uint16_t bg);


/**
 * @brief Sélectionne le mode d'affichage.
 *
 * Permet de choisir entre 4 modes d'affichage.
 *
 * @param mode
 *        - TFT_MODE_DEFAULT
 *        - TFT_MODE_1
 *        - TFT_MODE_2
 *        - TFT_MODE_3
 */
void tft_set_mode(uint8_t mode);