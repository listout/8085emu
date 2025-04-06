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

/*
 * Dump containts of the registers
 */
void
dump_registers(regs_t reg)
{
	printf("----------------------------------------\n");
	printf("-------------- Registers ---------------\n");
	printf("A: 0x%02X\tSP: 0x%02X\n", reg.A, reg.SP);
	printf("B: 0x%02X\tPC: 0x%02X\n", reg.B, reg.PC);
	printf("C: 0x%02X\tD: 0x%02X\n", reg.C, reg.D);
	printf("E: 0x%02X\tH: 0x%02X\n", reg.E, reg.H);
	printf("L: %02X\n", reg.L);
	printf("S: 0x%02X\tZ: 0x%02X\n", reg.S, reg.Z);
	printf("P: 0x%02X\tAC: 0x%02X\n", reg.P, reg.AC);
	printf("CY: 0x%02X\n", reg.CY);
	printf("----------------------------------------\n");
}

/*
 * Dump containts of the memory in 32 x 2048 grid
 */
void
dump_memory(mem_t mem)
{
	int count = 0;
	for (int i = 00; i < 2048; i++) {
		printf("%4d ", count);
		for (int j = 00; j < 32; j++) {
			printf("%02X ", mem.memory[count++]);
		}
		printf("\n");
	}
}

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
	regs->CY = 0;
	regs->SP = 0xFFFF;
	regs->PC = 0x0000;
}

/*
 * Fetch instruction from memory
 */
uint8_t
fetch(regs_t *regs, mem_t *mem)
{
	return mem->memory[regs->PC++];
}

/*
 * Parse and execute op-code from memory.
 *
 * @TODO: implement concept of cycles
 */
void
execute(regs_t *regs, mem_t *mem)
{
	uint8_t opcode = fetch(regs, mem);
	switch (opcode) {
	case 0x3E: { // MVI A
		uint8_t data = fetch(regs, mem);
		regs->A = data;
	} break;
	case 0x06: { // MVI B
		uint8_t data = fetch(regs, mem);
		regs->B = data;
	} break;
	case 0x0E: { // MVI C
		uint8_t data = fetch(regs, mem);
		regs->C = data;
	} break;
	case 0x16: { // MVI D
		uint8_t data = fetch(regs, mem);
		regs->D = data;
	} break;
	case 0x1E: { // MVI E
		uint8_t data = fetch(regs, mem);
		regs->E = data;
	} break;
	case 0x26: { // MVI H
		uint8_t data = fetch(regs, mem);
		regs->H = data;
	} break;
	case 0x2E: { // MVI L
		uint8_t data = fetch(regs, mem);
		regs->L = data;
	} break;
	case 0x36: { // MVI M
		uint8_t data = fetch(regs, mem);
		mem->memory[regs->H << 8 | regs->L] = data;
	} break;
	case 0x3A: { // LDA
		uint8_t lower_order_address = fetch(regs, mem);
		uint8_t higher_order_address = fetch(regs, mem);
		regs->A = mem->memory[higher_order_address << 8 | lower_order_address];
	} break;
	case 0x31: { // LXI SP
		uint8_t lower_order_address = fetch(regs, mem);
		uint8_t higher_order_address = fetch(regs, mem);
		regs->SP = higher_order_address << 8 | lower_order_address;
	} break;
	case 0x01: { // LXI B
		uint8_t data_c = fetch(regs, mem);
		uint8_t data_b = fetch(regs, mem);
		regs->C = data_c;
		regs->B = data_b;
	} break;
	case 0xC5: { // PUSH B
		mem->memory[regs->SP--] = regs->B;
		mem->memory[regs->SP--] = regs->C;

	} break;
	default:
		break;
	}
}

/*
 * Test function to check various op-codes
 */
void
test_run()
{
	regs_t *regs = malloc(sizeof(regs_t));
	mem_t *mem = malloc(sizeof(mem_t));
	reset_cpu(regs, mem);
	mem->memory[0x0000] = 0x3E;
	mem->memory[0x0001] = 0x05;
	execute(regs, mem);
	mem->memory[0x0002] = 0x26;
	mem->memory[0x0003] = 0x07;
	execute(regs, mem);
	mem->memory[0x0004] = 0x2E;
	mem->memory[0x0005] = 0xD0;
	execute(regs, mem);
	mem->memory[0x0006] = 0x36;
	mem->memory[0x0007] = 0x25;
	dump_registers(*regs);
	execute(regs, mem);
	mem->memory[0x0008] = 0x3A;
	mem->memory[0x0009] = 0xD0;
	mem->memory[0x000a] = 0x07;
	execute(regs, mem);
	dump_registers(*regs);
	/*dump_memory(*mem);*/
	free(regs);
	free(mem);
}

int
main(void)
{
	return EXIT_SUCCESS;
}
