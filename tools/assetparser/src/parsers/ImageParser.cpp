#include "ImageParser.hpp"
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include "../BinaryWrite.hpp"
#include "../thirdparty/stb_image/stb_image.h"

void ImageParser::ParseFile(const std::string& inputFile, 
    const std::string& outputFile)
{
    int32_t width       { 0 };
    int32_t height      { 0 };
    int32_t numChannels { 0 };

    uint8_t* data = stbi_load(inputFile.c_str(), &width, &height, &numChannels, 0);
    
    if(data == nullptr)
        throw std::runtime_error("Error parsing file \"" + inputFile + 
            "\" - " + stbi_failure_reason());
    
    std::ofstream os;
    os.open(outputFile, std::ios::out | std::ios::binary | std::ios::trunc);

    if(!os.is_open())
        throw std::runtime_error("Could not open file \"" + outputFile + 
            "\" to write ");

    WriteBytes(os, static_cast<uint16_t>(width));
    WriteBytes(os, static_cast<uint16_t>(height));
    WriteBytes(os, static_cast<uint8_t>(numChannels));
    WriteBytes(os, data, width * height * numChannels);
    os.close();

    stbi_image_free(data);
}