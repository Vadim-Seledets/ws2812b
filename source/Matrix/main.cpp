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
            for (uint8_t y = 0; y < MATRIX_HEIGHT; ++y)
            {
                clear();
                set_pixel(x, y, { ColorModel::RGB, {50, y * 2, 0} });
                show(vram, NUMBER_OF_BYTES);
                sleep(600);
            }
        }
    }
}
