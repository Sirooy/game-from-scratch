#include "ShaderParser.hpp"
#include "../BinaryWrite.hpp"
#include "../AssetParserManager.hpp"

namespace parser
{

ShaderParser::ShaderParser()
{
    options.SetOptimizationLevel(shaderc_optimization_level::shaderc_optimization_level_performance);
    options.SetSourceLanguage(shaderc_source_language::shaderc_source_language_glsl);
}

void ShaderParser::ParseFile(const AssetParserManager& apm, 
    const std::string& inputFile, 
    const std::string& inputExtension,
    const std::string& outputFile)
{
    std::string shaderSource       = GetShaderSourceCode(inputFile);
    shaderc_shader_kind shaderKind = GetShaderKindFromExtension(inputExtension);

    shaderc::CompilationResult result = compiler.CompileGlslToSpv(shaderSource,
        shaderKind, inputFile.c_str(), options);

    if(result.GetCompilationStatus() != shaderc_compilation_status_success)
        throw std::runtime_error("Error parsing shader \"" + inputFile + "\" - " +
            result.GetErrorMessage());

    std::ofstream os;
    os.open(outputFile, std::ios::out | std::ios::binary | std::ios::trunc);

    std::endian endianess = apm.Config().endianness;
    for(const uint32_t bytes : result)
    {
        WriteBytes(os, bytes, endianess);
    }

    os.close();
}

shaderc_shader_kind ShaderParser::GetShaderKindFromExtension(const std::string& ext)
{
    if(ext == "vert")
        return shaderc_shader_kind::shaderc_vertex_shader;
    else if(ext == "tesc")
        return shaderc_shader_kind::shaderc_tess_control_shader;
    else if(ext == "tese")
        return shaderc_shader_kind::shaderc_tess_evaluation_shader;
    else if(ext == "geom")
        return shaderc_shader_kind::shaderc_geometry_shader;
    else if(ext == "frag")
        return shaderc_shader_kind::shaderc_fragment_shader;
    else if(ext == "comp")
        return shaderc_shader_kind::shaderc_compute_shader;

    throw std::runtime_error("Invalid extension \"" + ext + "\"");
}

std::string ShaderParser::GetShaderSourceCode(const std::string& inputFile)
{
    std::ifstream is;
    is.open(inputFile, std::ios::ate | std::ios::binary);
    if(!is.is_open())
        throw std::runtime_error("Could not open file \"" + inputFile + "\"");

    size_t fileSize = static_cast<size_t>(is.tellg()); 
    std::string sourceCode(fileSize, '\0');

    is.seekg(0);
    is.read(sourceCode.data(), fileSize);
    is.close();

    return sourceCode;
}

} //namespace parser