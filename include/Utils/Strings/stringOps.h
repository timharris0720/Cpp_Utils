#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <locale>
#include <codecvt>

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
    std::string WcharToString(const wchar_t* wcharStr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wcharStr);
    }
    

}