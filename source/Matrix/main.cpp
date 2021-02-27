#include <avr/io.h>
#include "stdlib.h"
#include "util/delay.h"
#include "string.h"

void sleep(long long delayMs)
{
    for (long long i = delayMs; i > 0; i--)
        _delay_ms(1);
}

const uint8_t MATRIX_WIDTH = 4;
const uint8_t MATRIX_HEIGHT = 4;
const uint8_t NUMBER_OF_PIXELS = MATRIX_WIDTH * MATRIX_HEIGHT;
const uint16_t NUMBER_OF_BYTES = NUMBER_OF_PIXELS * 3;

uint8_t *vram = (uint8_t *)malloc(NUMBER_OF_BYTES * sizeof(uint8_t));

void show(uint8_t *bytes, uint16_t count)
{
    const uint8_t high = 1;
    const uint8_t low = 0;

    volatile uint8_t *ptr = bytes;
    volatile uint8_t value = *ptr++;
    volatile uint16_t byte_count = count;
    volatile uint8_t t1 = low, t2 = high;

    if (value & 0x80)
        t1 = high;

    asm volatile(
        "start:                             ;   clk        size  \n\t"
        // bit_7
        "    out     %[port], %[high]       ; 1 (1)          1   \n\t"
        "    mov     %[t2], %[high]         ; 2 (1)          1   \n\t"
        "    out     %[port], %[t1]         ; 3-1 (1)        1   \n\t"
        "    rjmp    .+0                    ; 5-3 (2)        1   \n\t"
        "    sbrs    %[value], 6            ; 6-4 (1)        1   \n\t"
        "    mov     %[t2], %[low]          ; 7-5 (1)        1   \n\t"
        "    out     %[port], %[low]        ; 7/8-5/6 (1)    1   \n\t"
        "    rjmp    .+0                    ; 2-7/8 (2)      1   \n\t"
        // bit 6
        "    out     %[port], %[high]       ; 1 (1)          1   \n\t"
        "    mov     %[t1], %[high]         ; 2 (1)          1   \n\t"
        "    out     %[port], %[t2]         ; 3-1 (1)        1   \n\t"
        "    rjmp    .+0                    ; 5-3 (2)        1   \n\t"
        "    sbrs    %[value], 5            ; 6-4 (1)        1   \n\t"
        "    mov     %[t1], %[low]          ; 7-5 (1)        1   \n\t"
        "    out     %[port], %[low]        ; 7/8-5/6 (1)    1   \n\t"
        "    rjmp    .+0                    ; 2-7/8 (2)      1   \n\t"
        // bit 5
        "    out     %[port], %[high]       ; 1 (1)          1   \n\t"
        "    mov     %[t2], %[high]         ; 2 (1)          1   \n\t"
        "    out     %[port], %[t1]         ; 3-1 (1)        1   \n\t"
        "    rjmp    .+0                    ; 5-3 (2)        1   \n\t"
        "    sbrs    %[value], 4            ; 6-4 (1)        1   \n\t"
        "    mov     %[t2], %[low]          ; 7-5 (1)        1   \n\t"
        "    out     %[port], %[low]        ; 7/8-5/6 (1)    1   \n\t"
        "    rjmp    .+0                    ; 2-7/8 (2)      1   \n\t"
        // bit 4
        "    out     %[port], %[high]       ; 1 (1)          1   \n\t"
        "    mov     %[t1], %[high]         ; 2 (1)          1   \n\t"
        "    out     %[port], %[t2]         ; 3-1 (1)        1   \n\t"
        "    rjmp    .+0                    ; 5-3 (2)        1   \n\t"
        "    sbrs    %[value], 3            ; 6-4 (1)        1   \n\t"
        "    mov     %[t1], %[low]          ; 7-5 (1)        1   \n\t"
        "    out     %[port], %[low]        ; 7/8-5/6 (1)    1   \n\t"
        "    rjmp    .+0                    ; 2-7/8 (2)      1   \n\t"
        // bit 3
        "    out     %[port], %[high]       ; 1 (1)          1   \n\t"
        "    mov     %[t2], %[high]         ; 2 (1)          1   \n\t"
        "    out     %[port], %[t1]         ; 3-1 (1)        1   \n\t"
        "    rjmp    .+0                    ; 5-3 (2)        1   \n\t"
        "    sbrs    %[value], 2            ; 6-4 (1)        1   \n\t"
        "    mov     %[t2], %[low]          ; 7-5 (1)        1   \n\t"
        "    out     %[port], %[low]        ; 7/8-5/6 (1)    1   \n\t"
        "    rjmp    .+0                    ; 2-7/8 (2)      1   \n\t"
        // bit 2
        "    out     %[port], %[high]       ; 1 (1)          1   \n\t"
        "    mov     %[t1], %[high]         ; 2 (1)          1   \n\t"
        "    out     %[port], %[t2]         ; 3-1 (1)        1   \n\t"
        "    rjmp    .+0                    ; 5-3 (2)        1   \n\t"
        "    sbrs    %[value], 1            ; 6-4 (1)        1   \n\t"
        "    mov     %[t1], %[low]          ; 7-5 (1)        1   \n\t"
        "    out     %[port], %[low]        ; 7/8-5/6 (1)    1   \n\t"
        "    rjmp    .+0                    ; 2-7/8 (2)      1   \n\t"
        // bit 1
        "    out     %[port], %[high]       ; 1 (1)          1   \n\t"
        "    mov     %[t2], %[high]         ; 2 (1)          1   \n\t"
        "    out     %[port], %[t1]         ; 3-1 (1)        1   \n\t"
        "    rjmp    .+0                    ; 5-3 (2)        1   \n\t"
        "    sbrs    %[value], 0            ; 6-4 (1)        1   \n\t"
        "    mov     %[t2], %[low]          ; 7-5 (1)        1   \n\t"
        "    out     %[port], %[low]        ; 7/8-5/6 (1)    1   \n\t"
        "    sbiw    %[byte_count], 1       ; 2-7/8 (2)      1   \n\t"
        // bit 0
        "    out     %[port], %[high]       ; 1 (1)          1   \n\t"
        "    mov     %[t1], %[high]         ; 2 (1)          1   \n\t"
        "    out     %[port], %[t2]         ; 3-1 (1)        1   \n\t"
        "    ld      %[value], %a[ptr]+     ; 5-3 (2)        1   \n\t"
        "    sbrs    %[value], 7            ; 6-4 (1)        1   \n\t"
        "    mov     %[t1], %[low]          ; 7-5 (1)        1   \n\t"
        "    out     %[port], %[low]        ; 7/8-5/6 (1)    1   \n\t"
        "    brne    start                  ; 2-7/8 (2)      1   \n\t"

        : [byte_count] "+w"(byte_count),
          [value]      "+r"(value),
          [t1]         "+r"(t1),
          [t2]         "+r"(t2)
        : [port]       "I"(_SFR_IO_ADDR(PORTD)),
          [ptr]        "e"(ptr),
          [high]       "r"(high),
          [low]        "r"(low));
}

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
	
	Color(ColorModel cm, RGB &value)
	: color_model(cm), rgb(value) {}
};

inline uint8_t xy_to_pixel_num(const uint8_t x, const uint8_t y)
{
	return ((x + 1) / 2) * (2 * MATRIX_HEIGHT - 1) + (x / 2) + (x % 2 == 0 ? y : -y);
}

void set_pixel(const uint8_t x, const uint8_t y, const Color color)
{
	const uint8_t pixel_num = xy_to_pixel_num(x, y);
	const uint8_t index = pixel_num * 3;
	vram[index] = color.rgb.green;
	vram[index + 1] = color.rgb.red;
	vram[index + 2] = color.rgb.blue;
}

int main(void)
{
    // Matrix initialization

    DDRD = 0x01;
    PORTD = 0x00;

	memset(vram, 0, NUMBER_OF_BYTES);

	RGB rgb{10, 0, 0};
	Color color{ColorModel::RGB, rgb};
    set_pixel(0, 3, color);

	show(vram, NUMBER_OF_BYTES);
	
    while (1)
    {
    }
}
