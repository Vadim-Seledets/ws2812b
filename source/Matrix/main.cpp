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

    clear();

    while (1)
    {
        for (uint8_t x = 0; x < 255; ++x)
        {
            for (uint8_t y = 0; y < 255; ++y)
            {
                set_pixel(3, 5, { ColorModel::RGB, {0, 10, 10} });
                show(vram, NUMBER_OF_BYTES);
            }
        }
    }
}
