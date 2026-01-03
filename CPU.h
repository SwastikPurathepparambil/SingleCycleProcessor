#include <iostream>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdint>
using namespace std;


// class instruction { // optional
// public:
// 	bitset<32> instr;//instruction
// 	instruction(bitset<32> fetch); // constructor

// };

class CPU {
private:
	int dmemory[4096]; //data memory byte addressable in little endian fashion;
	uint8_t* instructionMemory;
	unsigned long PC; //pc


public:
	CPU();
	unsigned long readPC();
	void incPC();
    void setInstMem(uint8_t *instMem);
	uint32_t pullInstruction(unsigned long PC);
	void runOneCycle();
};

// add other functions and objects here
