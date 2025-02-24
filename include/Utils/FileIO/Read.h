#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
namespace FileIO {
    std::vector<char> readFileBinary(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return {};
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        if (!file.read(buffer.data(), size)) {
            std::cerr << "Error reading file: " << filename << std::endl;
            return {};
        }

        return buffer;
    }
    std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return "";
        }
    
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return content;
    }
}