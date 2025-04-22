#pragma once
#include <limits>
#include <string>
#include <vector>
#include <cstdint>
#include <shaderc/shaderc.hpp>
#include "BaseParser.hpp"

namespace parser
{

class ShaderParser : public BaseParser
{
public:
    ShaderParser();

    void ParseFile(const AssetParserManager& apm, const std::string& inputFile, 
        const std::string& inputExtension, const std::string& outputFile) override;

    const std::vector<std::string>& GetInputExtensions() const override 
    { 
        return ShaderParser::m_InputExtensions; 
    }

    const std::string& GetOutputExtension() const override
    {
        return ShaderParser::m_OutputExtension;
    }

protected:
    static shaderc_shader_kind GetShaderKindFromExtension(const std::string& ext);
    static std::string GetShaderSourceCode(const std::string& inputFile);

protected:
    inline static const std::vector<std::string> m_InputExtensions { "vert", "tesc", "tese", "geom", "frag", "comp" };
    inline static constexpr std::string m_OutputExtension          { "spv" };

    shaderc::Compiler compiler      { };
    shaderc::CompileOptions options { };
};

} //namespace parser