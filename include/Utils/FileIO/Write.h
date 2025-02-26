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

        // Handle writing for a single value
        if constexpr (std::is_trivially_copyable_v<T>) {
            file.write(reinterpret_cast<const char*>(&data), sizeof(T));
        } 
        // Handle writing for a container (e.g., std::vector<T>)
        else if constexpr (requires { data.data(); data.size(); }) {  
            file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(typename T::value_type));
        } 
        else {
            static_assert(sizeof(T) == -1, "Unsupported type for binary writing");
        }

        file.close();
    }
}