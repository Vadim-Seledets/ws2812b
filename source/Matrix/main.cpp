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
	DDRB = 0x00;
	PORTB = 0x00;
	
    DDRD = 0x01;
    PORTD = 0x00;

    // Configure timer/counter 0 so that ISR is called at least 30 times per second

    TCCR0 = 0x0D; // Timer/Counter configuration
	TIMSK = 0x02; // Enable output compare match interrupt
	OCR0 = 0x81;
    
	clear();
	sei();
}

int main(void)
{
    init();

    uint8_t x = MATRIX_WIDTH / 2;
    uint8_t y = MATRIX_HEIGHT / 2;

	set_pixel(x, y, {ColorModel::RGB, {30, 0, 0}});

    while (1)
    {
        switch (PINB)
        {
            case 1:
                clear();
                if (x < MATRIX_WIDTH - 1)
                    x++;
                set_pixel(x, y, {ColorModel::RGB, {30, 0, 0}});
                _delay_ms(150);
                break;
            case 2:
                clear();
                if (y > 0)
                    y--;
                set_pixel(x, y, {ColorModel::RGB, {30, 0, 0}});
                _delay_ms(150);
                break;
            case 4:
                clear();
                if (y < MATRIX_HEIGHT - 1)
                    y++;
                set_pixel(x, y, {ColorModel::RGB, {30, 0, 0}});
                _delay_ms(150);
                break;
            case 8:
                clear();
                if (x > 0)
                    x--;
                set_pixel(x, y, {ColorModel::RGB, {30, 0, 0}});
                _delay_ms(150);
                break;
        }

        // for (uint8_t x = 0; x < MATRIX_WIDTH - 1; ++x)
        // {
        //     clear();
        //     set_pixel(x, 0, {ColorModel::RGB, {30, 0, 0}});
        //     _delay_ms(30);
        // }
        // for (uint8_t y = 0; y < MATRIX_HEIGHT; ++y)
        // {
        //     clear();
        //     set_pixel(MATRIX_WIDTH - 1, y, {ColorModel::RGB, {0, 30, 0}});
        //     _delay_ms(30);
        // }
        // for (uint8_t x = 14; x > 0; --x)
        // {
        //     clear();
        //     set_pixel(x, MATRIX_HEIGHT - 1, {ColorModel::RGB, {0, 0, 30}});
        //     _delay_ms(30);
        // }
        // for (uint8_t y = 15; y > 0; --y)
        // {
        //     clear();
        //     set_pixel(0, y, {ColorModel::RGB, {30, 30, 30}});
        //     _delay_ms(30);
        // }
    }
}
