#include "AssetParserManager.hpp"

void AssetParserManager::ParseFile(const std::filesystem::path& path) const
{
    if(!path.has_extension())
        throw std::runtime_error("File " + PathToString(path) + "does not have an extension");
    
    std::string inputFile  = PathToString(path);
    std::string outputFile = inputFile;
    std::string extension  = PathToString(path.extension()).substr(1);
    std::transform(extension.begin(), extension.end(), extension.begin(), 
        [](unsigned char c) { return std::tolower(c); } );

    auto find = parsersMap.find(extension);
    if(find != parsersMap.end())
    {
        BaseParser* parser     = find->second;
        outputFile = outputFile.replace(inputFile.rfind('.') + 1, 
            extension.length(), parser->GetOutputExtension());
        
        parser->ParseFile(inputFile, outputFile);
        std::cout << "File \"" << inputFile << "\" parsed succesfully.\n";
    }
    else
        throw std::runtime_error("Could not parse file: \"" + 
            inputFile + "\". Unsuported file extensions: \"" + 
            extension + "\"");
}

#if defined(PLATFORM_WINDOWS)
std::string AssetParserManager::PathToString(const std::filesystem::path::string_type& str)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    
    return converter.to_bytes(str);
}
#elif defined(PLATFORM_LINUX)
std::string AssetParserManager::PathToString(const std::filesystem::path::string_type& str)
{
    return str;
}
#endif