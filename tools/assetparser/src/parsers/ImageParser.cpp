#include "ImageParser.hpp"
#include <memory>
#include <fstream>
#include <stdexcept>
#include "../BinaryWrite.hpp"
#include "../AssetParserManager.hpp"
#include "../thirdparty/stb_image/stb_image.h"

namespace parser
{

void ImageParser::ParseFile(const AssetParserManager& apm, 
    const std::string& inputFile, 
    const std::string& outputFile)
{
    int32_t width            { 0 };
    int32_t height           { 0 };
    int32_t inputNumChannels { 0 };

    uint8_t* inputData = stbi_load(inputFile.c_str(), &width, &height, &inputNumChannels, 0);
    
    if(inputData == nullptr)
        throw std::runtime_error("Error parsing file \"" + inputFile + 
            "\" - " + stbi_failure_reason());
    
    std::ofstream os;
    os.open(outputFile, std::ios::out | std::ios::binary | std::ios::trunc);

    if(!os.is_open())
    {
        stbi_image_free(inputData);
        throw std::runtime_error("Could not open file \"" + outputFile + 
            "\" to write ");
    }
    
    ImageFormat inputFormat   = GetStbiFormatFromChannels(inputNumChannels);
    ImageFormat outputFormat  = inputFormat; //TODO: Read input format from config file
    int32_t outputNumChannels = GetNumChannelsFromFormat(outputFormat);
    
    std::endian endianess = apm.Config().endianness;
    WriteBytes(os, static_cast<uint16_t>(width), endianess);
    WriteBytes(os, static_cast<uint16_t>(height), endianess);
    WriteBytes(os, static_cast<uint8_t>(outputNumChannels), endianess); //TODO: Write the format instead of the number of channels

    if(inputFormat == outputFormat)
    {
        WriteBytes(os, inputData, width * height * inputNumChannels);
    }
    else
    {
        WriteImageWithDifferentFormat(os, inputData, inputFormat,
            outputFormat, width, height);
    }

    os.close();
    stbi_image_free(inputData);
}

void ImageParser::WriteImageWithDifferentFormat(std::ofstream& os, uint8_t* inputData, 
    ImageFormat inputFormat, ImageFormat outputFormat, int32_t width, int32_t height)
{
    int32_t inputNumChannels              = GetNumChannelsFromFormat(inputFormat);
    int32_t outputNumChannels             = GetNumChannelsFromFormat(outputFormat);
    int32_t numPixels                     = width * height;
    int32_t outputSize                    = numPixels * outputNumChannels;
    std::unique_ptr<uint8_t[]> outputData = std::make_unique<uint8_t[]>(outputSize);

    uint8_t* inputPtr          = inputData;
    uint8_t* outputPtr         = outputData.get();
    int32_t minChannelsToCopy  = std::min(inputNumChannels, outputNumChannels);
    const int32_t* inputTable  = FormatChannelIndices[static_cast<int32_t>(inputFormat)];
    const int32_t* outputTable = FormatChannelIndices[static_cast<int32_t>(outputFormat)];

    for(int32_t i = 0;i < numPixels; ++i)
    {
        int32_t channelIndex = 0;
        //Copy the minimun number of channels
        while(channelIndex < minChannelsToCopy)
        {
            outputPtr[outputTable[channelIndex]] = inputPtr[inputTable[channelIndex]];
            channelIndex++;
        }

        //Assign default values if the output format has more channels
        //than the input format
        while(channelIndex < outputNumChannels)
        {
            outputPtr[outputTable[channelIndex]] = DefaultChannelValues[channelIndex];
        }

        //Advance to the next pixel
        inputPtr  += inputNumChannels;
        outputPtr += outputNumChannels;
    }

    WriteBytes(os, outputData.get(), outputSize);
}

int32_t ImageParser::GetNumChannelsFromFormat(ImageFormat format)
{
    switch(format)
    {
        case ImageFormat::R:    return 1;
        case ImageFormat::RG:
        case ImageFormat::GR:   return 2;
        case ImageFormat::RGB:
        case ImageFormat::BGR:  return 3;
        case ImageFormat::RGBA: 
        case ImageFormat::BGRA:
        case ImageFormat::ARGB:
        case ImageFormat::ABGR: return 4;
        default: throw std::runtime_error("Unsupported format");
    }
}

ImageFormat ImageParser::GetFormatFromString(const std::string& str)
{
    if(str == "r")    return ImageFormat::R;
    if(str == "rg")   return ImageFormat::RG;
    if(str == "gr")   return ImageFormat::GR;
    if(str == "rgb")  return ImageFormat::RGB;
    if(str == "bgr")  return ImageFormat::BGR;
    if(str == "rgba") return ImageFormat::RGBA;
    if(str == "bgra") return ImageFormat::BGRA;
    if(str == "argb") return ImageFormat::ARGB;
    if(str == "abgr") return ImageFormat::ABGR;

    throw std::runtime_error("Invalid channel format \"" + str + "\"");
}

ImageFormat ImageParser::GetStbiFormatFromChannels(int32_t numChannels)
{
    switch (numChannels)
    {
        case 1: return ImageFormat::R;
        case 2: return ImageFormat::RG;
        case 3: return ImageFormat::RGB;
        case 4: return ImageFormat::RGBA;
    }

    throw std::runtime_error("Invalid number of channels");
}

} //namespace parser