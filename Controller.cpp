#include "Controller.h"
#include <cstdint>

Controller::Controller(uint8_t opcode) {
    
    // opcode = opcode;

    switch (opcode)
    {
		// U-type: LUI 
		// opcode = 0110111 (0x37)
		case 0x37: {
			RegWrite = 1;
            ALUSrc = 1;
            Branch = 0;
            MemRead = 0;
            MemWrite = 0;
            MemToReg = 0;
				
		}

		// R-type: register-register ALU
		// opcode = 0110011 (0x33)
		case 0x33: {
			RegWrite = 1;
            ALUSrc = 0;
            Branch = 0;
            MemRead = 0;
            MemWrite = 0;
            MemToReg = 0;
			break;
		}

		// I-type: immediate ALU / loads
		// opcode = 0010011 (0x13)
		case 0x13: { 	
			RegWrite = 1;
            ALUSrc = 1;
            Branch = 0;
            MemRead = 0;
            MemWrite = 0;
            MemToReg = 0;
			break;
		}    
        default: {
			RegWrite = 0;
            ALUSrc = 0;
            Branch = 0;
            MemRead = 0;
            MemWrite = 0;
            MemToReg = 0;
            break;
        }
        
    }

}