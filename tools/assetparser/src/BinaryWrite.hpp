#pragma once
#include <bit>
#include <cstdint>
#include <fstream>
#include <concepts>

inline void WriteBytes(std::ofstream& os, const char* bytes, std::streamsize amount)
{
    os.write(bytes, amount);
}

inline void WriteBytes(std::ofstream& os, const uint8_t* bytes, std::streamsize amount)
{
    os.write(reinterpret_cast<const char*>(bytes), amount);
}

template<typename T> requires std::is_integral_v<T>
inline void WriteBytes(std::ofstream& os, T n, std::endian endianness)
{
    if (endianness != std::endian::native)
        n = std::byteswap(n);

    os.write(reinterpret_cast<char*>(&n), sizeof(T));
}