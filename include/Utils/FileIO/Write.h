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
    void WriteFile(std::string& fileName, std::string& data, WriteType wt = WriteType::Append){
        std::ios_base::openmode fileMode = (wt == WriteType::Append) ? std::ios::app : std::ios::trunc;
        std::ofstream file(fileName, fileMode);

        if (!file) {
            std::cerr << "[ERROR : WRITE FILE] opening file: " << fileName << std::endl;
            return;
        }

        file << data;
        file.close();
    }
    void WriteFile_Binary(const std::string& filename, const std::vector<char>& data, WriteType mode) {
        std::ios_base::openmode fileMode = std::ios::binary;
        fileMode |= (mode == WriteType::Append) ? std::ios::app : std::ios::trunc;
    
        std::ofstream file(filename, fileMode);
        if (!file) {
            std::cerr << "[ERROR : WRITE FILE BINARY] Error opening file: " << filename << std::endl;
            return;
        }
    
        file.write(data.data(), data.size());
        file.close();
    }
}