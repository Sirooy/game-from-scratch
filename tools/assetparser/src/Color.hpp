#pragma once

//Foreground colors
namespace fcolor
{

inline constexpr const char* Black         = "\033[30m";
inline constexpr const char* BrightBlack   = "\033[30;1m";
inline constexpr const char* Red           = "\033[31m";
inline constexpr const char* BrightRed     = "\033[31;1m";
inline constexpr const char* Green         = "\033[32m";
inline constexpr const char* BrightGreen   = "\033[32;1m";
inline constexpr const char* Yellow        = "\033[33m";
inline constexpr const char* BrightYellow  = "\033[33;1m";
inline constexpr const char* Blue          = "\033[34m";
inline constexpr const char* BrightBlue    = "\033[34;1m";
inline constexpr const char* Magenta       = "\033[35m";
inline constexpr const char* BrightMagenta = "\033[35;1m";
inline constexpr const char* Cyan          = "\033[36m";
inline constexpr const char* BrightCyan    = "\033[36;1m";
inline constexpr const char* White         = "\033[37m";
inline constexpr const char* BrightWhite   = "\033[37;1m";
inline constexpr const char* Reset         = "\033[39;0m";

} // namespace fcolor

//Background colors
namespace bcolor
{

inline constexpr const char* Black         = "\033[40m";
inline constexpr const char* BrightBlack   = "\033[40;1m";
inline constexpr const char* Red           = "\033[41m";
inline constexpr const char* BrightRed     = "\033[41;1m";
inline constexpr const char* Green         = "\033[42m";
inline constexpr const char* BrightGreen   = "\033[42;1m";
inline constexpr const char* Yellow        = "\033[43m";
inline constexpr const char* BrightYellow  = "\033[43;1m";
inline constexpr const char* Blue          = "\033[44m";
inline constexpr const char* BrightBlue    = "\033[44;1m";
inline constexpr const char* Magenta       = "\033[45m";
inline constexpr const char* BrightMagenta = "\033[45;1m";
inline constexpr const char* Cyan          = "\033[46m";
inline constexpr const char* BrightCyan    = "\033[46;1m";
inline constexpr const char* White         = "\033[47m";
inline constexpr const char* BrightWhite   = "\033[47;1m";
inline constexpr const char* Reset         = "\033[49;0m";

} // namespace bcolor
