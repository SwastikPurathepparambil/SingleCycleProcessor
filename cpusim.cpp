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

		// get the opcode
		uint8_t OPCODE = instMem[PC_reg + 0] & 0x7F; // mask of 0b01111111 because we need the first 7 digits for opcode

		// print out the OPCODE in bits // good! got OPCODE
		cout << "Opcode byte (bin): " << std::bitset<8>(OPCODE) << endl;

		// based off OPCODE, now we want to determine type of instruction
		// Use a switch statement for this
		// for now we will add functionality for 3 OPCODES
		switch (OPCODE)
		{
			// THE 8TH BIT IS INCLUDED BECAUSE UINT8 BUT CAN IGNORE IT
			// L-type: 00110111
			case 55: {
				/* code */
				// step 1: let's see what bits 7-11 have
				// 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
				// 0  0  0  0  0  0  0 0 0 0 0 0 0 0 0 0

				// MOVE THIS DEF'N LATER
				uint8_t b0 = instMem[PC_reg + 0];
				uint8_t b1 = instMem[PC_reg + 1];
				uint16_t rd = (((uint16_t)b1 << 8) | b0) & 0x0F80;
				rd = rd >> 7;
				cout << "rd byte (bin): " << std::bitset<16>(rd) << endl;


				break;
			}
				// R-type: 00110011
			case 51: {
				/* code */
				break;
			}
				// I-type: 00010011
			case 19: {
				/* code */
				break;
			}		
			default: {
				break;
			}
		}

		
		// uint32_t inst = instMem[PC_reg + 3] + instMem[PC_reg + 2] + instMem[PC_reg + 1] + instMem[PC_reg + 0];
		// std::string str = std::to_string(inst);
		// cout << str << endl; 

		

		// decode
		
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