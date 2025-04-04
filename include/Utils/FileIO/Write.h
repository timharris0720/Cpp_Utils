#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
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

        // Check if the data is trivially copyable (single object)
        if (std::is_trivially_copyable<T>::value) {
            // Write single trivially copyable object
            file.write(reinterpret_cast<const char*>(&data), sizeof(T));
        }
        else {
            // If the data is a container (like std::vector), handle it
            if constexpr (std::is_same<T, std::vector<typename T::value_type>>::value) {
                // Ensure the value type is trivially copyable
                using ValueType = typename T::value_type;
                static_assert(std::is_trivially_copyable<ValueType>::value,
                              "Only trivially copyable types are supported in containers.");

                // Write the vector data
                file.write(reinterpret_cast<const char*>(data.data()),
                           data.size() * sizeof(ValueType));
            }
            else {
                // If it's not a container-like structure, trigger error
                static_assert(sizeof(T) == 0, "Unsupported type for binary writing.");
            }
        }

        file.close();
    }
}