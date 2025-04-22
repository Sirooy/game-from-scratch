#pragma once
#include <string>
#include <vector>

class AssetParserManager;

namespace parser
{

class BaseParser
{
public:
    BaseParser() = default;

    virtual void ParseFile(const AssetParserManager& apm, const std::string& inputFile, 
        const std::string& inputExtension, const std::string& outputFile) = 0;
    virtual const std::vector<std::string>& GetInputExtensions() const = 0;
    virtual const std::string& GetOutputExtension() const = 0;
};

} //namespace parser