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
	
	RGB rgb{0, 10, 0};
	Color color{ColorModel::RGB, rgb};
    set_pixel(3, 5, color);
	set_pixel(4, 5, color);

	show(vram, NUMBER_OF_BYTES);
	
    while (1)
    {
    }
}
