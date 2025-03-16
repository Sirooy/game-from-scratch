#pragma once
#include <string>
#include <vector>

class BaseParser
{
public:
    BaseParser() = default;

    virtual void ParseFile(const std::string& inputFile, const std::string& outputFile) = 0;
    virtual const std::vector<std::string>& GetInputExtensions() const = 0;
    virtual const std::string& GetOutputExtension() const = 0;
};