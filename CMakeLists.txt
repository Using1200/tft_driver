idf_component_register(
    SRCS "tft_gfx.c" "tft_hal.c" "tft_init.c" 
    INCLUDE_DIRS "."
    REQUIRES driver
)