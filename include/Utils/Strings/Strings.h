#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <sstream>
#include <utf8/utf8.h>

#ifdef _WIN32
#include <windows.h>
#endif
namespace String {
    std::string StripString(std::string str, std::string stripChar = "")
    {
        if (str.length() != 0)
        {
            auto w = std::string(stripChar);
            auto n = std::string("\n");
            auto r = std::string("\t");
            auto t = std::string("\r");
            auto v = std::string(1, str.front());
            while ((v == t) || (v == r) || (v == n) || (v == w))
            {
                str.erase(str.begin());
                v = std::string(1, str.front());
            }
            v = std::string(1, str.back());
            while ((v == t) || (v == r) || (v == n) || (v == w))
            {
                str.erase(str.end() - 1);
                v = std::string(1, str.back());
            }
        }
        return str;
    }
    std::vector<std::string> SplitString(const std::string& istr, const std::string& del, int maxSplits = -1) {
        std::vector<std::string> arr;

        int strleng = istr.length();
        int delleng = del.length();
        if (delleng == 0)
            return arr; // no change

        int i = 0;
        int k = 0;
        int splitCount = 0;

        while (i < strleng) {
            int j = 0;
            while (i + j < strleng && j < delleng && istr[i + j] == del[j])
                j++;
            if (j == delleng) { // found delimiter
                arr.push_back(istr.substr(k, i - k));
                i += delleng;
                k = i;
                splitCount++;
                if (splitCount >= maxSplits && maxSplits != -1) {
                    break; // stop splitting after reaching the max number of splits
                }
            }
            else {
                i++;
            }
        }
        // Add the remaining part of the string after the last delimiter
        arr.push_back(istr.substr(k, strleng - k));
        return arr;
    }
    std::string RemovePrefix(std::string str, std::string prefix) {
        
        return str.substr(prefix.length());
    }
    std::string RemoveSuffix(std::string str, std::string suffix) {
        return str.substr(0, str.length() - suffix.length());
    }
    bool Contains(std::string str, std::string sstr) {
        if (str.find(sstr) != std::string::npos) {
            return true; // substring found
        }
        else {
            return false; // substring not found
        }
    }
    std::string Replace(std::string inputString, std::string substring, std::string replacement) {
        bool allOccurencesFound = false;
        
        size_t index = 0;
        while (true) {
            /* Locate the substring to replace. */
            index = inputString.find(substring, index);
            if (index == std::string::npos) break;

            /* Make the replacement. */
            inputString = inputString.replace(index, substring.size(), replacement);

            /* Advance index forward so the next iteration doesn't pick it up as well. */
            index += replacement.size();
        }
        return inputString;
    }
    std::string WcharToChar(WCHAR* wstr) {
        #ifdef _WIN32
            if (!wstr) return "";
        
            int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
            std::string str(size_needed, 0);
            WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &str[0], size_needed, nullptr, nullptr);
        
            return str;
        #else
            size_t len = wcslen(wstr) * 4 + 1;  // Allocate enough space
            char* buffer = new char[len];
            wcstombs(buffer, wstr, len);
            std::string str(buffer);
            delete[] buffer;
            return str;
        #endif
    }
    std::string charArrayToLetterString(std::vector<char> buffer){
        std::string result(buffer.begin(), buffer.end()); // Convert vector to string

        // Remove all null characters ('\0')
        result.erase(std::remove(result.begin(), result.end(), '\0'), result.end());    

        return result;
    }

    std::string utf16_to_utf8(const std::u16string& input) {
        std::string output;
        utf8::utf16to8(input.begin(), input.end(), std::back_inserter(output));
        return output;
    }
    std::string utf16le_to_utf8(const char16_t* data, size_t max_chars) {
        std::u16string utf16(data, max_chars);

        // Trim null terminator if present
        size_t end = utf16.find(u'\0');
        if (end != std::u16string::npos) {
            utf16 = utf16.substr(0, end);
        }

        std::string output;
        utf8::utf16to8(utf16.begin(), utf16.end(), std::back_inserter(output));
        return output;
    }
    template< typename T >
    std::string int_to_hex( T my_integer )
    {
        std::stringstream sstream;
        sstream << "0x" << std::hex << my_integer;
        return sstream.str();
    }
    std::string displayParse(std::vector<char> arr){
        std::string str;
        for(int i = 0; i < arr.size(); i++){
            if(arr[i] != 0x00){
                str += arr[i];
            }
        }
        return str;
    }
    std::string toNumericString(const char* arr, int leng) {
        return std::string(arr, leng);
    }

}