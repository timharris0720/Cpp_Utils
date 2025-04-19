#pragma once
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <cstring>

class Int24 {
private:
    int32_t value;

public:
    Int24() : value(0) {}

    // Construct from int32_t
    Int24(int32_t v) {
        // Clamp to 24-bit signed range
        if (v < -0x800000 || v > 0x7FFFFF) {
            throw std::out_of_range("Int24 value out of range");
        }
        value = v;
    }

    // Read from 3 bytes (little-endian)
    static Int24 fromBytes(const uint8_t* bytes) {
        int32_t val = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16);

        // Sign extension for negative values
        if (val & 0x800000) {
            val |= 0xFF000000;
        }

        return Int24(val);
    }

    // Convert to 3 bytes (little-endian)
    void toBytes(uint8_t* out) const {
        out[0] = value & 0xFF;
        out[1] = (value >> 8) & 0xFF;
        out[2] = (value >> 16) & 0xFF;
    }

    // Implicit conversion to int
    operator int32_t() const {
        return value;
    }

    int32_t toInt() const {
        return value;
    }

    // Arithmetic and assignment
    Int24& operator=(int32_t v) {
        if (v < -0x800000 || v > 0x7FFFFF) {
            throw std::out_of_range("Int24 value out of range");
        }
        value = v;
        return *this;
    }

    Int24 operator+(const Int24& other) const {
        return Int24(value + other.value);
    }

    Int24 operator-(const Int24& other) const {
        return Int24(value - other.value);
    }

    Int24& operator+=(const Int24& other) {
        value += other.value;
        return *this;
    }

    Int24& operator-=(const Int24& other) {
        value -= other.value;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Int24& i24) {
        os << i24.value;
        return os;
    }
};
