#pragma once
#include <iostream>
#include <fstream>
#include <array>
#include <cstdint>
#include <vector>
#include <locale>
#include <codecvt>
#include <type_traits>

namespace Memory {
    char readByte(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        char value;
        if (!file.read(reinterpret_cast<char*>(&value), 1)) {
            std::cerr << "Error reading file!" << std::endl;
            return char{};
        }
        return value;
    }
    int readInt32(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        int value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(int))) {
            std::cerr << "Error reading file!" << std::endl;
            return int{};
        }
        return value;
    }
    unsigned int readUInt32(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        unsigned int value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(unsigned int))) {
            std::cerr << "Error reading file!" << std::endl;
            return int{};
        }
        return value;
    }
    int64_t readInt64(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        int64_t value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(int64_t))) {
            std::cerr << "Error reading file!" << std::endl;
            return int64_t{};
        }
        return value;
    }
    uint64_t readUInt64(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        uint64_t value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(uint64_t))) {
            std::cerr << "Error reading file!" << std::endl;
            return uint64_t{};
        }
        return value;
    }
    
    int32_t readInt24(std::ifstream& file, std::streampos offset) {
        file.seekg(offset, std::ios::beg);  // Move to the correct offset
    
        std::array<uint8_t, 3> buffer = {0, 0, 0};  // Buffer to hold 3 bytes
        if (!file.read(reinterpret_cast<char*>(buffer.data()), 3)) {
            std::cerr << "Error reading 24-bit integer from file!" << std::endl;
            return 0;
        }
    
        // Convert 3-byte buffer into a 32-bit signed integer
        int32_t value = (buffer[0]) | (buffer[1] << 8) | (buffer[2] << 16);
    
        // Sign extension for 24-bit signed integers
        if (value & 0x800000) {  // If the 24th bit (0x800000) is set, it's negative
            value |= 0xFF000000;  // Extend the sign to 32 bits
        }
    
        return value;
    }

    unsigned short readUint16(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        unsigned short value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(unsigned short))) {
            std::cerr << "Error reading file!" << std::endl;
            return uint16_t{};
        }
        return value;
    }

    short readInt16(std::ifstream& file, std::streampos offset){
        file.seekg(offset);
        short value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(short))) {
            std::cerr << "Error reading file!" << std::endl;
            return short{};
        }
        return value;
    }

    float readFloat(std::ifstream& file, std::streampos offset){ // 4BYTE
        file.seekg(offset);
        float value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(float))) {
            std::cerr << "Error reading file!" << std::endl;
            return uint16_t{};
        }
        return value;
    }

    double readDouble(std::ifstream& file, std::streampos offset){ // 8 BYTE
        file.seekg(offset);
        double value;
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(double))) {
            std::cerr << "Error reading file!" << std::endl;
            return uint16_t{};
        }
        return value;
    }
    template <typename T>
    std::vector<T> readBytes(std::ifstream& file, std::streampos offset, int byteToRead = 1){
        std::vector<T> buffer(byteToRead);
        if (!file.read(reinterpret_cast<char*>(buffer.data()), byteToRead * sizeof(T))) {
            std::cerr << "Error reading file!" << std::endl;
            return std::vector<T>{};  // Return empty vector
        }
        return buffer;
    }
    template <typename T>
    T readType(std::ifstream& file, std::streampos offset, int byteToRead = 1){
        T buffer(byteToRead);
        if (!file.read(reinterpret_cast<char*>(buffer), byteToRead * sizeof(T))) {
            std::cerr << "Error reading file!" << std::endl;
            return T{};  // Return empty vector
        }
        return buffer;
    }
}