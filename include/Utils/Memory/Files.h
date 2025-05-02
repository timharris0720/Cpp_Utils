#pragma once
#include <iostream>
#include <fstream>
#include <array>
#include <cstdint>
#include <vector>
#include <locale>
#include <codecvt>
#include <type_traits>
#include "../Types.h"
namespace Memory {
    inline char readByte(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        char value;
        if (!file.read(reinterpret_cast<char*>(&value), 1)) {
            std::cerr << "Error reading file!" << std::endl;
            return char{};
        }
        return value;
    }
    inline int readInt32(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        int value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(int))) {
            std::cerr << "Error reading file!" << std::endl;
            return 0;
        }
        return value;
    }
    inline unsigned int readUInt32(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        unsigned int value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(unsigned int))) {
            std::cerr << "Error reading file!" << std::endl;
            return 0;
        }
        return value;
    }
    inline int64_t readInt64(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        int64_t value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(int64_t))) {
            std::cerr << "Error reading file!" << std::endl;
            return 0;
        }
        return value;
    }
    inline uint64_t readUInt64(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        uint64_t value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(uint64_t))) {
            std::cerr << "Error reading file!" << std::endl;
            return 0;
        }
        return value;
    }
    

    inline unsigned short readUint16(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        unsigned short value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(unsigned short))) {
            std::cerr << "Error reading file!" << std::endl;
            return uint16_t{};
        }
        return value;
    }

    inline short readInt16(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        short value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(short))) {
            std::cerr << "Error reading file!" << std::endl;
            return short{};
        }
        return value;
    }

    inline float readFloat(std::ifstream& file, std::streampos offset){ // 4BYTE
        file.seekg(offset);
        float value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(float))) {
            std::cerr << "Error reading file!" << std::endl;
            return 0.0;
        }
        return value;
    }

    inline double readDouble(std::ifstream& file, std::streampos offset){ // 8 BYTE
        file.seekg(offset);
        double value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(double))) {
            std::cerr << "Error reading file!" << std::endl;
            return 0.0;
        }
        return value;
    }
    template <typename T>
    inline std::vector<T> readBytes(std::ifstream& file, std::streampos offset, int byteToRead = 1){
        file.seekg(offset);
        std::vector<T> buffer(byteToRead);
        if (!file.read(reinterpret_cast<char*>(buffer.data()), byteToRead * sizeof(T))) {
            std::cerr << "Error reading file!" << std::endl;
            
            return std::vector<T>{};  // Return empty vector
            
        }
        return buffer;
    }
    template <typename T>
    inline T readType(std::ifstream& file, std::streampos offset,int size = sizeof(T)){
        file.seekg(offset);
        T buffer(size);
        if (!file.read(reinterpret_cast<char*>(&buffer), size)) {
            std::cerr << "Error reading file! readtype" << std::endl;
            return T{};  // Return empty vector
        }
        return buffer;
    }

    inline Int24 readInt24(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        uint8_t buf[3];
        if (!file.read(reinterpret_cast<char*>(&buf), 3)) {
            std::cerr << "Error reading file!" << std::endl;
            return 0;
        }
        Int24 blockNumber = Int24::fromBytes(buf);
        return blockNumber;
    }
    inline int32_t readInt24AsInt32(Int24 value) {
        uint8_t blockBytes[3] = {0};
        value.toBytes(blockBytes);
        // Combine the 3 bytes into a single 24-bit number
        int32_t blockNumber = (static_cast<int32_t>(blockBytes[0])) |
                            (static_cast<int32_t>(blockBytes[1]) << 8) |
                            (static_cast<int32_t>(blockBytes[2]) << 16);

        // Handle sign extension for the int24 -> int32 conversion
        if (blockNumber & 0x00800000) {  // Check if the sign bit is set (24th bit)
            blockNumber |= 0xFF000000;    // Sign-extend to 32-bit
        }

        return blockNumber;
    }

}
