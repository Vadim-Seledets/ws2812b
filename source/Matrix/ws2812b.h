#ifndef WS2812B_H_
#define WS2812B_H_

#include <avr/io.h>
#include "stdlib.h"
#include "string.h"

const uint8_t MATRIX_WIDTH = 16;
const uint8_t MATRIX_HEIGHT = 16;
const uint16_t NUMBER_OF_PIXELS = MATRIX_WIDTH * MATRIX_HEIGHT;
const uint16_t NUMBER_OF_BYTES = NUMBER_OF_PIXELS * 3;

extern uint8_t *vram;

enum class ColorModel {
    RGB,
    HSL // Not yet implemented
};

struct RGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    
    RGB(uint8_t r, uint8_t g, uint8_t b)
        : red(r), green(g), blue(b) {}
};

struct HSL {
    uint8_t hue;
    uint8_t saturation;
    uint8_t lightness;
};

struct Color
{
    ColorModel color_model;
    union
    {
        RGB rgb;
        HSL hsl;
    };
    
    Color(ColorModel cm, RGB value)
        : color_model(cm), rgb(value) {}
};

inline uint8_t xy_to_pixel_num(const uint8_t x, const uint8_t y)
{
    return ((x + 1) / 2) * (2 * MATRIX_HEIGHT - 1) + (x / 2) + (x % 2 == 0 ? y : -y);
}

inline void clear()
{
    memset(vram, 0, NUMBER_OF_BYTES);
}

void show(uint8_t *bytes, uint16_t count);
void set_pixel(const uint8_t x, const uint8_t y, const Color color);

#endif /* WS2812B_H_ */