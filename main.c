#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEM 65536

typedef struct Memory {
	uint8_t memory[MAX_MEM];
} mem_t;

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

void
reset_cpu(regs_t regs, mem_t mem)
{
	memset(&regs, 0, sizeof(regs));
	memset(&mem, 0, sizeof(mem));
	regs.PC = 0x0000;
void
reset_cpu(regs_t *regs, mem_t *mem)
{
	regs->A = 0;
	regs->B = 0;
	regs->C = 0;
	regs->D = 0;
	regs->E = 0;
	regs->H = 0;
	regs->L = 0;
	regs->S = 0;
	regs->Z = 0;
	regs->AC = 0;
	regs->P = 0;
	regs->CY = 1;
	regs->SP = 0xFFFF;
	regs->PC = 0x0000;
}

/*
 * Fetch instruction from memory
 */
uint8_t
fetch(regs_t *regs, mem_t mem)
{
	return mem.memory[regs->PC++];
}
}

int
main(void)
{
	return EXIT_SUCCESS;
}
