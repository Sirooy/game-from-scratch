#pragma once
#include <string>
#include <vector>
#include "BaseParser.hpp"

/* ##### FORMAT ##### */
/*
-- Little Endian --
uint16_t  - Width
uint16_t  - Height
uint8_t   - Num channels
uint8_t[] - [Width * Height * Num channels] Image bytes (R|RG|RGB|RGBA)
*/
/* ##### ###### ##### */

class ImageParser : public BaseParser
{
public:
    void ParseFile(const std::string& inputFile, const std::string& outputFile) override;

    const std::vector<std::string>& GetInputExtensions() const override 
    { 
        return ImageParser::m_InputExtensions; 
    }

    const std::string& GetOutputExtension() const override
    {
        return ImageParser::m_OutputExtension;
    }

protected:
    inline static const std::vector<std::string> m_InputExtensions { "png", "jpg", "jpeg", "bmp", "gif", "tga", "psd" };
    inline static constexpr std::string m_OutputExtension          { "img" };
};