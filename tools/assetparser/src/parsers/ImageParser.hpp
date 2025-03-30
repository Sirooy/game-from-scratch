#pragma once
#include <limits>
#include <string>
#include <vector>
#include <cstdint>
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

namespace parser
{

enum class ChannelIndex
{
    R = 0,
    G = 1,
    B = 2,
    A = 3,
    NumChannels
};

enum class ImageFormat : uint8_t
{
    R = 0,
    RG,
    GR,
    RGB,
    BGR,
    RGBA,
    BGRA,
    ARGB,
    ABGR,
    NumFormats
};

class ImageParser : public BaseParser
{
public:
    void ParseFile(const AssetParserManager& apm, const std::string& inputFile, 
        const std::string& outputFile) override;

    const std::vector<std::string>& GetInputExtensions() const override 
    { 
        return ImageParser::m_InputExtensions; 
    }

    const std::string& GetOutputExtension() const override
    {
        return ImageParser::m_OutputExtension;
    }

protected:
    void WriteImageWithDifferentFormat(std::ofstream& os, uint8_t* inputData, 
        ImageFormat inputFormat, ImageFormat outputFormat, int32_t width, int32_t height);

    static int32_t GetNumChannelsFromFormat(ImageFormat format);
    static ImageFormat GetFormatFromString(const std::string& str);
    static ImageFormat GetStbiFormatFromChannels(int32_t numChannels);

protected:
    inline static const std::vector<std::string> m_InputExtensions { "png", "jpg", "jpeg", "bmp", "gif", "tga", "psd" };
    inline static constexpr std::string m_OutputExtension          { "img" };
    //Default values to assign when converting from a format with less channels than the output format (Ex. R -> RGBA)
    inline static constexpr int32_t DefaultChannelValues[static_cast<int32_t>(ChannelIndex::NumChannels)]
    {
      //R  G  B  A
        0, 0, 0, std::numeric_limits<uint8_t>::max()
    };
    //Table indicating the position that a certain channel index occupies in a specific format
    //(Ex. In the format ARGB, The channel index R(= 0) maps to the position/index 1 in the format)
    //This table is used for conversions between image formats
    inline static constexpr int32_t FormatChannelIndices
        [static_cast<int32_t>(ImageFormat::NumFormats)][static_cast<int32_t>(ChannelIndex::NumChannels)]
    { 
        //R  G  B  A
        { 0, 0, 0, 0}, //R
        { 0, 1, 0, 0}, //RG
        { 1, 0, 0, 0}, //GR
        { 0, 1, 2, 0}, //RGB
        { 2, 1, 0, 0}, //BGR
        { 0, 1, 2, 3}, //RGBA
        { 2, 1, 0, 3}, //BGRA
        { 1, 2, 3, 0}, //ARGB
        { 3, 2, 1, 0}  //ABGR
    };
};

} //namespace parser