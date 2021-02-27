#include <avr/io.h>
#include "util/delay.h"
#include "ws2812b.h"

void sleep(long long delayMs)
{
    for (long long i = delayMs; i > 0; i--)
        _delay_ms(1);
}

int main(void)
{
    // Matrix initialization

    DDRD = 0x01;
    PORTD = 0x00;

    while (1)
    {
        for (uint8_t x = 0; x < MATRIX_WIDTH; ++x)
        {
            clear();
            set_pixel(x, 0, {ColorModel::RGB, {30, 0, 0}});
            show(vram, NUMBER_OF_BYTES);
            sleep(300);
        }
        for (uint8_t y = 0; y < MATRIX_HEIGHT; ++y)
        {
            clear();
            set_pixel(MATRIX_WIDTH - 1, y, {ColorModel::RGB, {0, 30, 0}});
            show(vram, NUMBER_OF_BYTES);
            sleep(300);
        }
        for (uint8_t x = 14; x > 0; ++x)
        {
            clear();
            set_pixel(x, MATRIX_HEIGHT - 1, {ColorModel::RGB, {0, 0, 30}});
            show(vram, NUMBER_OF_BYTES);
            sleep(300);
        }
        for (uint8_t y = 14; y > 0; ++y)
        {
            clear();
            set_pixel(0, y, {ColorModel::RGB, {30, 30, 30}});
            show(vram, NUMBER_OF_BYTES);
            sleep(300);
        }
    }
}
