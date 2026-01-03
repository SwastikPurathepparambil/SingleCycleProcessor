#include "CPU.h"
#include <cstdint>
#include "Controller.h"


CPU::CPU()
{
	PC = 0; //set PC to 0
	instructionMemory = nullptr;
	// for (int i = 0; i < 4096; i++) //copy instrMEM
	// {
	// 	dmemory[i] = (0);
	// }
}


unsigned long CPU::readPC()
{
	return PC;
}

void CPU::incPC()
{
	PC += 4;
}

void CPU::setInstMem(uint8_t* instMem)
{
	instructionMemory = instMem;
	// Testing
	// uint8_t b0 = *(instructionMemory + 0); // bits [7:0]
	// uint8_t b1 = *(instructionMemory + 1); // bits [15:8]
	// uint8_t b2 = *(instructionMemory + 2); // bits [23:16]
	// uint8_t b3 = *(instructionMemory + 3); // bits [31:24]

	// uint32_t instr = (uint32_t)b0 | ((uint32_t)b1 << 8) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 24);
	// uint8_t opcode = instr & 0x7F;
	// cout << "First Opcode: " << std::bitset<7>(opcode) << endl;
}

uint32_t CPU::pullInstruction(unsigned long PC) {
	uint8_t b0 = *(instructionMemory + PC + 0); // bits [7:0]
	uint8_t b1 = *(instructionMemory + PC + 1); // bits [15:8]
	uint8_t b2 = *(instructionMemory + PC + 2); // bits [23:16]
	uint8_t b3 = *(instructionMemory + PC + 3); // bits [31:24]

	uint32_t instr = (uint32_t)b0 | ((uint32_t)b1 << 8) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 24);
	return instr;
}

void CPU::runOneCycle() {
	// could make this a private variable
	uint32_t currInstr = pullInstruction(PC);
	uint8_t opcode = currInstr & 0x7F;

	Controller controller = Controller(opcode);
	

}