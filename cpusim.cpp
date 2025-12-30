#include "CPU.h"

#include <iostream>
#include <bitset>
#include <stdio.h>
#include<stdlib.h>
#include <string>
#include<fstream>
#include <sstream>
#include <cstdint>
#include <algorithm>
using namespace std;

/*
Add all the required standard and developed libraries here
*/

/*
Put/Define any helper function/definitions you need here
*/

// Helper function 1: used in to ensure that infile line
// passes through a hex input
bool is_hex(const std::string& s) {
    if (s.empty()) {
        return false;
    }

    // all_of allows you to look at the whole string in a quicker notation
    return std::all_of(s.begin(), s.end(), [](unsigned char c) {
        return std::isxdigit(c);
    });
}

int main(int argc, char* argv[])
{
	/* This is the front end of your project.
	You need to first read the instructions that are stored in a file and load them into an instruction memory.
	*/

	/* Each cell should store 1 byte. You can define the memory either dynamically, or define 
	it as a fixed size with size 4KB (i.e., 4096 lines). Each instruction is 32 bits (i.e., 4 lines, 
	saved in little-endian mode).
	
	Each line in the input file is stored as an hex and is 1 byte (each four lines are one instruction). 
	You need to read the file line by line and store it into the memory. You may need a mechanism to 
	convert these values to bits so that you can read opcodes, operands, etc.
	*/

	uint8_t instMem[4096];


	if (argc < 2) {
		//cout << "No file name entered. Exiting...";
		return -1;
	}

	ifstream infile(argv[1]); //open the file
	if (!(infile.is_open() && infile.good())) {
		cout<<"error opening file\n";
		return 0; 
	}
	string line; 
	int i = 0;
	while (infile) {
			infile>>line;
			
			// set up so that only look at lines where there is size is 8 (32 bit)
			// and must have only be hex numbers, use helper, good enough of a constraint for now...
			if (line.size() == 8 and is_hex(line)) {
				cout << line << ":" << line.size() << endl;
				
				// store the line as bytes instead of strings
				uint32_t fourbyte = static_cast<uint32_t>(std::stoul(line, nullptr, 16));

				
				// use masks to get the various bytes
				// then save as little endian
				uint8_t b0 = fourbyte & 0xFF;
				uint8_t b1 = (fourbyte >> 8) & 0xFF;
				uint8_t b2 = (fourbyte >> 16) & 0xFF;
				uint8_t b3 = (fourbyte >> 24) & 0xFF;

				// now store as little endian
				instMem[i + 0] = b0;
				instMem[i + 1] = b1;
				instMem[i + 2] = b2;
				instMem[i + 3] = b3;

				i += 4;
			}
			
	}
	int maxPC= i; 

	/* Instantiate your CPU object here.  CPU class is the main class in this project that defines different components of the processor.
	CPU class also has different functions for each stage (e.g., fetching an instruction, decoding, etc.).
	*/

	CPU myCPU;  // call the approriate constructor here to initialize the processor...  
	// make sure to create a variable for PC and resets it to zero (e.g., unsigned int PC = 0); 

	/* OPTIONAL: Instantiate your Instruction object here. */
	//Instruction myInst;

	bool done = true;
	while (done == true) // processor's main loop. Each iteration is equal to one clock cycle.  
	{

		//fetch 

		// Step 1: read in the instruction from memory
		// CPU accesses the instruction from instMem using PC
		int PC_reg = myCPU.readPC();
		// cout << "MSB: " << static_cast<int>(instMem[PC_reg + 0]) << endl;


		uint8_t b0 = instMem[PC_reg + 0]; // bits [7:0]
		uint8_t b1 = instMem[PC_reg + 1]; // bits [15:8]
		uint8_t b2 = instMem[PC_reg + 2]; // bits [23:16]
		uint8_t b3 = instMem[PC_reg + 3]; // bits [31:24]

		// Reconstruct full 32-bit instruction
		uint32_t instr = (uint32_t)b0 | ((uint32_t)b1 << 8) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 24);

		// Decode
		uint8_t opcode = instr & 0x7F; // bits [6:0]

		cout << "Opcode (bin): " << std::bitset<7>(opcode) << endl;

		switch (opcode)
		{
			// U-type: LUI / AUIPC
			// opcode = 0110111 (0x37)
			case 0x37: {
				uint8_t rd = (instr >> 7) & 0x1F;        
				uint32_t imm = instr & 0xFFFFF000;       

				cout << "U-type instruction" << endl;
				cout << "rd:  " << (int)rd << endl;
				cout << "imm: " << std::bitset<32>(imm) << endl;

				break;
			}

			// R-type: register-register ALU
			// opcode = 0110011 (0x33)
			case 0x33: {
				uint8_t rd     = (instr >> 7)  & 0x1F;
				uint8_t funct3 = (instr >> 12) & 0x07;
				uint8_t rs1    = (instr >> 15) & 0x1F;
				uint8_t rs2    = (instr >> 20) & 0x1F;
				uint8_t funct7 = (instr >> 25) & 0x7F;

				cout << "R-type instruction" << endl;
				cout << "rd:     " << (int)rd << endl;
				cout << "rs1:    " << (int)rs1 << endl;
				cout << "rs2:    " << (int)rs2 << endl;
				cout << "funct3: " << std::bitset<3>(funct3) << endl;
				cout << "funct7: " << std::bitset<7>(funct7) << endl;

				break;
			}

			// I-type: immediate ALU / loads
			// opcode = 0010011 (0x13)
			case 0x13: {
				uint8_t rd     = (instr >> 7)  & 0x1F;
				uint8_t funct3 = (instr >> 12) & 0x07;
				uint8_t rs1    = (instr >> 15) & 0x1F;

				// sign-extended immediate
				int32_t imm = ((int32_t)instr) >> 20;

				cout << "I-type instruction" << endl;
				cout << "rd:     " << (int)rd << endl;
				cout << "rs1:    " << (int)rs1 << endl;
				cout << "funct3: " << std::bitset<3>(funct3) << endl;
				cout << "imm:    " << imm << endl;

				break;
			}

			default:
				cout << "Unknown opcode" << endl;
				break;
		}
		
		// ... 
		myCPU.incPC();
		if (myCPU.readPC() > maxPC) {
			cout << "MY CPU: " << myCPU.readPC() << "maxPC: " << maxPC << endl;
			break;
		}
			
	}
	int a0 =0;
	int a1 =0;  
	// print the results (you should replace a0 and a1 with your own variables that point to a0 and a1)
	  cout << "(" << a0 << "," << a1 << ")" << endl;
	
	return 0;

}