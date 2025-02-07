#include <iostream>
#include <vector>
#include <cstdint>

class Crc32{
public:
    Crc32(){
        generateTable();
    }
    
    ~Crc32(){
    }

    uint32_t compute(const uint8_t* data, 
        size_t length, 
        uint32_t crc = 0xFFFFFFFF) 
    {
        for (size_t i = 0; i < length; ++i) {
            uint8_t index = (crc ^ data[i]) & 0xFF;
            crc = (crc >> 8) ^ table[index];
        }
        return crc ^ 0xFFFFFFFF;
    }

    uint32_t compute(std::vector<uint8_t>& data) {
        return compute(data.data(), data.size());
    }
private:
    uint32_t table[256];

    void generateTable(){
        const uint32_t polynomial = 0xEDB88320;
        for (uint32_t i = 0; i < 256; ++i) {
            uint32_t crc = i;
            for (int j = 0; j < 8; ++j) {
                if (crc & 1) {
                    crc = (crc >> 1) ^ polynomial;
                } else {
                    crc >>= 1;
                }
            }
            table[i] = crc;
        }//end for i
    }
};

Crc32 crc32;

int main(){
    std::string data = "Hello World!";
    uint32_t crc = crc32.compute(reinterpret_cast<const uint8_t*>(data.c_str()), data.size());
    std::cout << "CRC32: " << std::hex << crc << std::endl;
    return 0;
}


