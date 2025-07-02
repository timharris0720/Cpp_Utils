#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
namespace FileIO {

    class FileReader {
        private:
        int currentDepth = 0;
        std::string filename;
        std::vector<std::string> fileLines;
        public:
        FileReader() = default;
        FileReader(const std::string& filename){
            this->filename = filename;
            fileLines = ReadLines();
        }
        std::vector<char> ReadBinary(){
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
        std::string Read(){
            std::ifstream file(filename);
            if (!file) {
                std::cerr << "Error opening file: " << filename << std::endl;
                return "";
            }
        
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();
            return content;
        }
        std::vector<std::string> ReadLines(){
            std::ifstream file(filename);
            std::vector<std::string> lines;
            std::string line;
        
            if (!file.is_open()) {
                std::cerr << "Could not open file: " << filename << std::endl;
                return lines;
            }
        
            while (std::getline(file, line)) {
                lines.push_back(line);
            }
        
            return lines;
        }
        std::string ReadLine(){
            if(currentDepth < fileLines.size()){
                std::string line = fileLines[currentDepth];
                currentDepth++;
                return line;
            }
            else{
                return "";
            }
        }
        bool Peek(){
            return currentDepth < fileLines.size();
        }
    };

    inline std::vector<char> readFileBinary(const std::string& filename) {
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
    inline std::string readFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return "";
        }
    
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return content;
    }
    inline std::vector<std::string> readFileLines(const std::string& filename) {
        std::ifstream file(filename);
        std::vector<std::string> lines;
        std::string line;
    
        if (!file.is_open()) {
            std::cerr << "Could not open file: " << filename << std::endl;
            return lines;
        }
    
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
    
        return lines;
    }
}
