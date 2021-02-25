#include <avr/io.h>
#include "stdlib.h"

const uint8_t NUMBER_OF_PIXELS = 9;
const uint16_t NUMBER_OF_BYTES = NUMBER_OF_PIXELS * 3;

const uint8_t values[NUMBER_OF_BYTES] = {
	0, 10, 0,
	10, 0, 0,
	0, 0, 10
};

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

		: [value]      "+r" (value),
		  [byte_count] "+w" (byte_count),
		  [t1]         "+r" (t1),
		  [t2]         "+r" (t2)
		: [port]	   "I" (_SFR_IO_ADDR(PORTD)),
		  [ptr]        "e" (ptr),
		  [high]       "r" (high),
		  [low]        "r" (low)
	);
}

int main(void)
{
	// Matrix initialization
	
	DDRD = 0x01;
	PORTD = 0x00;
	
	uint8_t *bytes = (uint8_t *)malloc(NUMBER_OF_BYTES * sizeof(uint8_t));
	for (uint8_t i = 0; i < NUMBER_OF_BYTES; ++i)
		bytes[i] = values[i];
	
	show(bytes, NUMBER_OF_BYTES);
	
    while (1) 
    {
    }
}
