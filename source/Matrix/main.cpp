#include <avr/io.h>
#include "ws2812b.h"

#define F_CPU 8000000UL

#include "util/delay.h"

void sleep(long long delayMs)
{
    for (long long i = delayMs; i > 0; i--)
        _delay_ms(1);
}

ISR (TIMER0_COMP_vect)
{
	cli();
	show(vram, NUMBER_OF_BYTES);
	sei();
}

void init()
{
    DDRD = 0x01;
    PORTD = 0x00;

    // Configure timer/counter 0 so that ISR is called at least 30 times per second

    TCCR0 = 0x0D; // Timer/Counter configuration
	TIMSK = 0x02; // Enable output compare match interrupt
	OCR0 = 0x81;
    
	sei();
}

int main(void)
{
    init();

	clear();

    while (1)
    {
        for (uint8_t x = 0; x < MATRIX_WIDTH - 1; ++x)
        {
            clear();
            set_pixel(x, 0, {ColorModel::RGB, {30, 0, 0}});
            _delay_ms(60);
        }
        for (uint8_t y = 0; y < MATRIX_HEIGHT; ++y)
        {
            clear();
            set_pixel(MATRIX_WIDTH - 1, y, {ColorModel::RGB, {0, 30, 0}});
            _delay_ms(60);
        }
        for (uint8_t x = 14; x > 0; --x)
        {
            clear();
            set_pixel(x, MATRIX_HEIGHT - 1, {ColorModel::RGB, {0, 0, 30}});
            _delay_ms(60);
        }
        for (uint8_t y = 15; y > 0; --y)
        {
            clear();
            set_pixel(0, y, {ColorModel::RGB, {30, 30, 30}});
            _delay_ms(60);
        }
    }
}
