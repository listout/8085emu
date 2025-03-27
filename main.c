#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Registers {
	uint8_t A; // Accumulator
	uint8_t B;
	uint8_t C;
	uint8_t D;
	uint8_t E;
	uint8_t H;
	uint8_t L;

	uint16_t SP; // Stack pointer
	uint16_t PC; // Program counter

	/*Status Registers*/
	uint8_t S : 1;  // sign flag
	uint8_t Z : 1;  // zero flag
	uint8_t AC : 1; // auxiliary carrry flag
	uint8_t P : 1;  // parity flag
	uint8_t CY : 1; // carry (also called CS)
} regs_t;
int
main(void)
{
	return EXIT_SUCCESS;
}
