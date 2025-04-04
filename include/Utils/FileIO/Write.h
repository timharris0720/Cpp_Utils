#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
namespace FileIO {
    enum WriteType{
        Append = 0,
        Overwrite
    };
    void WriteFile(std::string fileName, std::string data, WriteType wt = WriteType::Append){
        std::ios_base::openmode fileMode = (wt == WriteType::Append) ? std::ios::app : std::ios::trunc;
        std::ofstream file(fileName, fileMode);

        if (!file) {
            std::cerr << "[ERROR : WRITE FILE] opening file: " << fileName << std::endl;
            return;
        }

        file << data;
        file.close();
    }
    template <typename T>
void WriteFile_Binary(const std::string& filename, const T& data, WriteType mode) {
    std::ios_base::openmode fileMode = std::ios::binary;
    fileMode |= (mode == WriteType::Append) ? std::ios::app : std::ios::trunc;

    std::ofstream file(filename, fileMode);
    if (!file) {
        std::cerr << "[ERROR: WRITE FILE BINARY] Error opening file: " << filename << std::endl;
        return;
    }

    if constexpr (std::is_trivially_copyable_v<T>) {
        // Trivially copyable type (e.g., int, float, char, POD struct)
        file.write(reinterpret_cast<const char*>(&data), sizeof(T));
    } 
    else if constexpr (
        requires {
            typename T::value_type;
            data.data();
            data.size();
        } && std::is_trivially_copyable_v<typename T::value_type>) 
    {
        // A container of trivially copyable elements (e.g., std::vector<char>)
        file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(typename T::value_type));
    } 
    else {
        static_assert(sizeof(T) == 0, "Unsupported type for binary writing");
    }

    file.close();
}