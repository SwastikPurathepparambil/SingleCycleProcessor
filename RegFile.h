#include <cstdint>

class RegFile
{
private:
    
public:
    uint32_t registers[32];
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    RegFile();
    ~RegFile();
};

