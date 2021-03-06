#ifndef WS2812B_H_
#define WS2812B_H_

#include <avr/io.h>
#include <avr/interrupt.h>
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

const Color Black = { ColorModel::RGB, { 0, 0, 0 } };
const Color White = { ColorModel::RGB, { 255, 255, 255 } };
const Color Red = { ColorModel::RGB, { 255, 0, 0 } };
const Color Lime = { ColorModel::RGB, { 0, 255, 0 } };
const Color Blue = { ColorModel::RGB, { 0, 0, 255 } };
const Color Yellow = { ColorModel::RGB, { 255, 255, 0 } };
const Color Cyan = { ColorModel::RGB, { 0, 255, 255 } };
const Color Magenta = { ColorModel::RGB, { 255, 0, 255 } };
const Color Silver = { ColorModel::RGB, { 192, 192, 192 } };
const Color Gray = { ColorModel::RGB, { 128, 128, 128 } };
const Color Maroon = { ColorModel::RGB, { 128, 0, 0 } };
const Color Olive = { ColorModel::RGB, { 128, 128, 0 } };
const Color Green = { ColorModel::RGB, { 0, 128, 0 } };
const Color Purple = { ColorModel::RGB, { 128, 0, 128 } };
const Color Teal = { ColorModel::RGB, { 0, 128, 128 } };
const Color Navy = { ColorModel::RGB, { 0, 0, 128 } };

// const Color Black = { ColorModel::RGB, { 0, 0, 0 } };
// const Color White = { ColorModel::RGB, { 25, 25, 25 } };
// const Color Red = { ColorModel::RGB, { 25, 0, 0 } };
// const Color Lime = { ColorModel::RGB, { 0, 25, 0 } };
// const Color Blue = { ColorModel::RGB, { 0, 0, 25 } };
// const Color Yellow = { ColorModel::RGB, { 25, 25, 0 } };
// const Color Cyan = { ColorModel::RGB, { 0, 25, 25 } };
// const Color Magenta = { ColorModel::RGB, { 25, 0, 25 } };
// const Color Silver = { ColorModel::RGB, { 19, 19, 19 } };
// const Color Gray = { ColorModel::RGB, { 13, 13, 13 } };
// const Color Maroon = { ColorModel::RGB, { 13, 0, 0 } };
// const Color Olive = { ColorModel::RGB, { 13, 13, 0 } };
// const Color Green = { ColorModel::RGB, { 0, 13, 0 } };
// const Color Purple = { ColorModel::RGB, { 13, 0, 13 } };
// const Color Teal = { ColorModel::RGB, { 0, 13, 13 } };
// const Color Navy = { ColorModel::RGB, { 0, 0, 13 } };

inline uint8_t xy_to_pixel_index(const uint8_t x, const uint8_t y)
{
    return ((x + 1) / 2) * (2 * MATRIX_HEIGHT - 1) + (x / 2) + (x % 2 == 0 ? y : -y);
}

inline void clear()
{
    cli();
    memset(vram, 0, NUMBER_OF_BYTES);
    sei();
}

void show(uint8_t *bytes, uint16_t count);
void set_pixel(const uint8_t x, const uint8_t y, const Color color);

/** @param lightness the range is [0, 100]% */
Color set_lightness(const Color color, const uint8_t lightness);

#endif /* WS2812B_H_ */
