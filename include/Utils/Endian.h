#pragma once
namespace Endian {
    namespace B2L {
        template<typename T>
        T swap64(T val) {
            return ((val >> 56) & 0x00000000000000FFULL) |
                ((val >> 40) & 0x000000000000FF00ULL) |
                ((val >> 24) & 0x0000000000FF0000ULL) |
                ((val >> 8)  & 0x00000000FF000000ULL) |
                ((val << 8)  & 0x000000FF00000000ULL) |
                ((val << 24) & 0x0000FF0000000000ULL) |
                ((val << 40) & 0x00FF000000000000ULL) |
                ((val << 56) & 0xFF00000000000000ULL);
        }
        template<typename T>
        T swap32(T val) {
            return ((val >> 24) & 0x000000FF) |
                ((val >> 8)  & 0x0000FF00) |
                ((val << 8)  & 0x00FF0000) |
                ((val << 24) & 0xFF000000);
        }
        template<typename T>
        T swap16(T val) {
            return (val >> 8) | (val << 8);
        }

        template<typename T>
        T swap24(T val) {
            uint32_t b0 = (val >> 16) & 0xFF;
            uint32_t b1 = (val >> 8) & 0xFF;
            uint32_t b2 = val & 0xFF;
            int32_t result = (b2 << 16) | (b1 << 8) | b0;

            // Sign extension for signed 24-bit
            if (result & 0x800000)
                result |= 0xFF000000;

            return result;
        }
        
    }
    namespace L2B {
        template<typename T>
        T swap64(T val) {
            return ((val >> 56) & 0x00000000000000FFULL) |
           ((val >> 40) & 0x000000000000FF00ULL) |
           ((val >> 24) & 0x0000000000FF0000ULL) |
           ((val >> 8)  & 0x00000000FF000000ULL) |
           ((val << 8)  & 0x000000FF00000000ULL) |
           ((val << 24) & 0x0000FF0000000000ULL) |
           ((val << 40) & 0x00FF000000000000ULL) |
           ((val << 56) & 0xFF00000000000000ULL);
        }
        template<typename T>
        T swap32(T val) {
            return ((val >> 24) & 0x000000FF) |
                ((val >> 8)  & 0x0000FF00) |
                ((val << 8)  & 0x00FF0000) |
                ((val << 24) & 0xFF000000);
        }
        template<typename T>
        T swap16(T val) {
            return (val >> 8) | (val << 8);
        }
        template<typename T>
        T swap24(T val){
            uint32_t b0 = val & 0xFF;
            uint32_t b1 = (val >> 8) & 0xFF;
            uint32_t b2 = (val >> 16) & 0xFF;
            int32_t result = (b0 << 16) | (b1 << 8) | b2;

            if (result & 0x800000)
                result |= 0xFF000000;

            return result;
        }
    }
}