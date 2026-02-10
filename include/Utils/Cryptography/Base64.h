#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>

namespace Cryptography {
    namespace Base64 {
        static const char B64_TABLE[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

        static inline unsigned char b64_value(char c)
        {
            if (c >= 'A' && c <= 'Z') return c - 'A';
            if (c >= 'a' && c <= 'z') return c - 'a' + 26;
            if (c >= '0' && c <= '9') return c - '0' + 52;
            if (c == '+') return 62;
            if (c == '/') return 63;
            return 255;
        }
        inline std::string base64_decode(const std::string& input) {
            std::vector<uint8_t> output;
            size_t i = 0;

            while (i < input.size())
            {
                uint32_t buf = 0;
                int pad = 0;

                for (int j = 0; j < 4 && i < input.size(); ++j)
                {
                    char c = input[i++];
                    if (c == '=')
                    {
                        buf <<= 6;
                        pad++;
                    }
                    else
                    {
                        unsigned char val = b64_value(c);
                        if (val == 255) { j--; continue; }
                        buf = (buf << 6) | val;
                    }
                }

                for (int j = 0; j < 3 - pad; ++j)
                {
                    output.push_back((buf >> (16 - j * 8)) & 0xFF);
                }
            }
            return std::string(output.begin(), output.end());
        }
        inline std::string base64_encode(const uint8_t* data, size_t size)
        {
            std::string output;
            output.reserve(((size + 2) / 3) * 4);

            for (size_t i = 0; i < size; i += 3)
            {
                uint32_t chunk = 0;
                int padding = 0;

                chunk |= data[i] << 16;

                if (i + 1 < size)
                    chunk |= data[i + 1] << 8;
                else
                    padding++;

                if (i + 2 < size)
                    chunk |= data[i + 2];
                else
                    padding++;

                output.push_back(B64_TABLE[(chunk >> 18) & 0x3F]);
                output.push_back(B64_TABLE[(chunk >> 12) & 0x3F]);

                if (padding < 2)
                    output.push_back(B64_TABLE[(chunk >> 6) & 0x3F]);
                else
                    output.push_back('=');

                if (padding < 1)
                    output.push_back(B64_TABLE[chunk & 0x3F]);
                else
                    output.push_back('=');
            }

            return output;
        }

        std::string base64_encode(const std::vector<uint8_t>& data)
        {
            return base64_encode(data.data(), data.size());
        }

        std::string base64_encode(const std::string& text)
        {
            return base64_encode(
                reinterpret_cast<const uint8_t*>(text.data()),
                text.size()
            );
        }
    }
}