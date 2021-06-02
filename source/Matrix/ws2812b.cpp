#include "ws2812b.h"

uint8_t *vram = (uint8_t *) malloc(NUMBER_OF_BYTES * sizeof(uint8_t));

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

    :   [byte_count] "+w"(byte_count),
        [value]      "+r"(value),
        [t1]         "+r"(t1),
        [t2]         "+r"(t2)
    :   [port]       "I"(_SFR_IO_ADDR(PORTD)),
        [ptr]        "e"(ptr),
        [high]       "r"(high),
        [low]        "r"(low));
}

void set_pixel(const uint8_t x, const uint8_t y, const Color color)
{
    const uint8_t pixel_index = xy_to_pixel_index(x, y);
    const uint16_t byte = pixel_index * 3;
	cli();
    vram[byte] = color.rgb.green;
    vram[byte + 1] = color.rgb.red;
    vram[byte + 2] = color.rgb.blue;
    sei();
}

Color set_lightness(Color color, const uint8_t lightness)
{
    const uint8_t red = color.rgb.red * lightness / 100;
    const uint8_t green = color.rgb.green * lightness / 100;
    const uint8_t blue = color.rgb.blue * lightness / 100;
    return { ColorModel::RGB, { red, green, blue } };
}
