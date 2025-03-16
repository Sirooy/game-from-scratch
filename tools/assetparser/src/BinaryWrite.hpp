#pragma once
#include <bit>
#include <cstdint>
#include <fstream>
#include <concepts>

#if defined(BIG_ENDIAN)
inline static constexpr std::endian Endianess = std::endian::big;
#elif defined(LITTLE_ENDIAN)
inline static constexpr std::endian Endianess = std::endian::little;
#else
inline static constexpr std::endian Endianess = std::endian::native;
#endif

template<typename T> requires std::is_integral_v<T>
inline void WriteBytes(std::ofstream& os, T n)
{
    if constexpr (Endianess != std::endian::native)
        n = std::byteswap(n);

    os.write(reinterpret_cast<char*>(&n), sizeof(T));
}

inline void WriteBytes(std::ofstream& os, const char* bytes, std::streamsize amount)
{
    os.write(bytes, amount);
}

inline void WriteBytes(std::ofstream& os, const uint8_t* bytes, std::streamsize amount)
{
    os.write(reinterpret_cast<const char*>(bytes), amount);
}