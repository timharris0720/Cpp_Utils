#pragma once
#include <iostream>
#include <fstream>
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
    template <typename T>
    std::vector<T> readByteAmounts(std::ifstream& file, std::streampos offset, int byteToRead = 1){
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