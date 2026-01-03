#include <iostream>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdint>
using namespace std;

class Controller
{
private:
    uint8_t opcode;
    

public:
    int RegWrite;
    int ALUSrc;
    int Branch;
    int MemRead;
    int MemWrite;
    int MemToReg;
    
    int PCSrc;
    Controller(uint8_t opcode);
    ~Controller();
};
