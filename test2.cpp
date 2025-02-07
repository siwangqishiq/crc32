#include <iostream>
#include <vector>
#include <cstdint>
#include <cstring>

const uint32_t POLY = 0xEDB88320;

// 预计算 CRC32 查找表
std::vector<uint32_t> generate_crc32_table() {
    std::vector<uint32_t> table(256);
    for (uint32_t i = 0; i < 256; ++i) {
        uint32_t crc = i;
        for (int j = 0; j < 8; ++j) {
            if (crc & 1) {
                crc = (crc >> 1) ^ POLY;
            } else {
                crc >>= 1;
            }
        }
        table[i] = crc;
    }
    return table;
}

uint32_t crc32(const uint8_t* data, size_t length) {
    static const std::vector<uint32_t> table = generate_crc32_table();
    uint32_t crc = 0xFFFFFFFF;
    
    for (size_t i = 0; i < length; ++i) {
        uint8_t index = (crc ^ data[i]) & 0xFF;
        crc = (crc >> 8) ^ table[index];
    }
    
    return crc ^ 0xFFFFFFFF;
}
int main() {
    const char* test_string = "Hello";
    uint32_t checksum = crc32(reinterpret_cast<const uint8_t*>(test_string), strlen(test_string));
    std::cout << "CRC32 Checksum: " << std::hex << checksum << std::endl;
    return 0;
}