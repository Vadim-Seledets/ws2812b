#include <avr/io.h>
#include <avr/pgmspace.h>
#include "ws2812b.h"

#define F_CPU 8000000UL

#include "util/delay.h"

void sleep(long long delayMs)
{
    for (long long i = delayMs; i > 0; i--)
        _delay_ms(1);
}

const uint8_t COLOR_VALUES[5 * 3] PROGMEM = {
    0, 0, 0,        // black
    255, 255, 255,  // white
    255, 0, 0,      // red
    0, 255, 0,      // lime
    0, 0, 255,      // blue
};

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

    // TCCR0 = 0x0D; // Timer/Counter configuration
	// TIMSK = 0x02; // Enable output compare match interrupt
	// OCR0 = 0x81;
	
	clear();
	sei();
}

/** do not call this function if you use auto frame refresh */
void draw()
{
    set_pixel(7, 0, Red);
    set_pixel(2, 11, Cyan);
    set_pixel(8, 0, Red);
    set_pixel(9, 0, Red);
    set_pixel(9, 1, Red);
    set_pixel(10, 1, Red);
    set_pixel(6, 1, Red);
    set_pixel(6, 2, Red);
    set_pixel(6, 3, Red);
    set_pixel(6, 4, Red);
    set_pixel(5, 4, Red);
    set_pixel(5, 5, Red);
    set_pixel(4, 6, Red);
    set_pixel(7, 4, Red);
    set_pixel(7, 5, Red);
    set_pixel(7, 6, Red);
    set_pixel(7, 9, Red);
    set_pixel(7, 10, Red);
    set_pixel(7, 11, Red);
    set_pixel(8, 5, Red);
    set_pixel(8, 6, Red);
    set_pixel(8, 7, Red);
    set_pixel(8, 8, Red);
    set_pixel(8, 9, Red);
    set_pixel(8, 10, Red);
    set_pixel(9, 6, Red);
    set_pixel(9, 7, Red);
    set_pixel(9, 8, Red);
    set_pixel(10, 1, Red);
    set_pixel(2, 13, Red);
    set_pixel(2, 14, Red);
    set_pixel(3, 8, Yellow);
    set_pixel(4, 7, Yellow);
    set_pixel(4, 8, Yellow);
    set_pixel(5, 6, Yellow);
    set_pixel(5, 7, Yellow);
    set_pixel(5, 8, Yellow);
    set_pixel(6, 6, Yellow);
    set_pixel(6, 7, Yellow);
    set_pixel(6, 8, Yellow);
    set_pixel(7, 7, Yellow);
    set_pixel(3, 11, Cyan);
    set_pixel(4, 10, Cyan);
    set_pixel(5, 10, Cyan);
    set_pixel(2, 10, Green);
    set_pixel(3, 9, Green);
    set_pixel(3, 10, Green);
    set_pixel(4, 9, Green);
    set_pixel(5, 9, Green);
    set_pixel(2, 12, Blue);
    set_pixel(3, 12, Blue);
    set_pixel(3, 13, Blue);
    set_pixel(4, 11, Blue);
    set_pixel(4, 12, Blue);
    set_pixel(5, 11, Blue);
    set_pixel(6, 9, Blue);
    set_pixel(6, 10, Blue);
    set_pixel(7, 8, Blue);
    set_pixel(8, 2, Black);
    set_pixel(9, 4, Black);
    set_pixel(9, 2, { ColorModel::RGB, { 19, 18, 11 } }); 
	set_pixel(9, 3, { ColorModel::RGB, { 19, 18, 11 } }); 
    set_pixel(10, 2, { ColorModel::RGB, { 19, 18, 11 } });
    set_pixel(10, 3, { ColorModel::RGB, { 19, 18, 11 } });
    set_pixel(10, 4, { ColorModel::RGB, { 19, 18, 11 } });
    set_pixel(7, 1, White);
    set_pixel(7, 2, White);
    set_pixel(7, 3, White);
    set_pixel(8, 1, White);
    set_pixel(8, 3, White);
    set_pixel(8, 4, White);

    show(vram, NUMBER_OF_BYTES);
}

int main(void)
{
    init();

    draw();

	// const uint8_t c = pgm_read_byte(&(COLOR_VALUES[0]));

    // uint8_t x = MATRIX_WIDTH / 2;
    // uint8_t y = MATRIX_HEIGHT / 2;

	// set_pixel(x, y, {ColorModel::RGB, {30, 0, 0}});

    while (1)
    {
        // switch (PINB)
        // {
        //     case 1:
        //         clear();
        //         if (x < MATRIX_WIDTH - 1)
        //             x++;
        //         set_pixel(x, y, {ColorModel::RGB, {30, 0, 0}});
        //         _delay_ms(150);
        //         break;
        //     case 2:
        //         clear();
        //         if (y > 0)
        //             y--;
        //         set_pixel(x, y, {ColorModel::RGB, {30, 0, 0}});
        //         _delay_ms(150);
        //         break;
        //     case 4:
        //         clear();
        //         if (y < MATRIX_HEIGHT - 1)
        //             y++;
        //         set_pixel(x, y, {ColorModel::RGB, {30, 0, 0}});
        //         _delay_ms(150);
        //         break;
        //     case 8:
        //         clear();
        //         if (x > 0)
        //             x--;
        //         set_pixel(x, y, {ColorModel::RGB, {30, 0, 0}});
        //         _delay_ms(150);
        //         break;
        // }

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
