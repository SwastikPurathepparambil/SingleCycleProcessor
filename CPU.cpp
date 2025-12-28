#include "CPU.h"


CPU::CPU()
{
	PC = 0; //set PC to 0
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

// Add other functions here ... 