#include "AssetParserManager.hpp"
#include "Color.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

#define CONFIG_OUTPUT_DIR_KEY "outputDir"
#define CONFIG_ENDIAN_KEY "endian"

namespace fs = std::filesystem;
using json   = nlohmann::json;

//Pass the directory as a copy in order to make it preferred
void AssetParserManager::ParseSingleFile(fs::path path) const
{
    path.make_preferred();

    if(!fs::exists(path))
        throw std::runtime_error("File " + path.string() + "does not exists");
    
    if(!fs::is_regular_file(path))
        throw std::runtime_error("\"" + path.string() + "\" is not a file");

    ParseFile(path);
}

//Pass the directory as a copy in order to make it preferred
void AssetParserManager::ParseDirectory(fs::path rootDirectory)
{
    rootDirectory.make_preferred();

    if(!fs::exists(rootDirectory))
        throw std::runtime_error("Directory \"" + rootDirectory.string() + 
            "\" does not exists");
    
    if(!fs::is_directory(rootDirectory))
        throw std::runtime_error("\"" + rootDirectory.string() + 
            "\" is not a directory");
    
    //Try to set the config
    fs::path configPath = rootDirectory / "config.json";
    if(fs::exists(configPath))
    {
        config.rootDir = rootDirectory;
        ParseConfigFile(configPath);
    }

    auto [files, directories] = GetFilesAndDirectories(rootDirectory, configPath);

    CreateDirectories(directories);
    ParseFiles(files);
}

void AssetParserManager::SetOutputDirectory(fs::path outputDir)
{
    outputDir.make_preferred();
    
    config.outputDir = std::move(outputDir);
}

AssetParserManager::FilesAndDirectories AssetParserManager::GetFilesAndDirectories(
    const std::filesystem::path& rootDirectory, 
    const std::filesystem::path& configPath)
{
    std::vector<fs::path> files { };
    std::vector<fs::path> directories { };

    //Include the root output path to be created
    if(config.HasOutputDir()) directories.emplace_back(config.outputDir);

    fs::recursive_directory_iterator it { rootDirectory };
    for(const auto& entry : it)
    {
        fs::path path = entry.path();

        //Ignore config file
        if(entry == configPath) 
            continue; 
        
        //Ignore files that dont have a parser
        if(fs::is_regular_file(path) && path.has_extension() && 
            !parsersMap.contains(GetPathExtension(path)))
            continue;

        //Add directories to be created only when there is an output path in the config
        if(entry.is_directory() && config.HasOutputDir())
            directories.emplace_back(ReplaceRootDirWithConfigOutputDir(path));
        else if(entry.is_regular_file())
            files.emplace_back(std::move(path));
    }

    return std::make_tuple(std::move(files), std::move(directories));
}

fs::path AssetParserManager::ReplaceRootDirWithConfigOutputDir(
    const fs::path& path) const
{
    std::string resultStr    = path.string();
    std::string rootDirStr   = config.rootDir.string();
    std::string outputDirStr = config.outputDir.string();

    resultStr.replace(0, rootDirStr.length(), outputDirStr);

    return fs::path { resultStr };
}

void AssetParserManager::CreateDirectories(const std::vector<std::filesystem::path> directories)
{
    for(const auto& directory : directories)
    {
        try
        {
            if(!fs::exists(directory))
            {
                if(fs::create_directories(directory))
                    std::cout << fcolor::BrightYellow << "\"" << directory.string() 
                        << "\" directory created" << '\n' << fcolor::Reset;
                else
                    throw std::runtime_error("Failed to create directory \"" + 
                        directory.string() + "\"");
            }
        }
        catch(const std::exception& e)
        {
            std::cout << bcolor::BrightRed << fcolor::Yellow << "[ERROR]: " << 
                bcolor::Reset << fcolor::Red << e.what() << '\n' << fcolor::Reset;
        }
    }
}

void AssetParserManager::ParseFiles(const std::vector<std::filesystem::path>& files)
{
    for(const auto& file : files)
    {
        try
        {
            ParseFile(file);
        }
        catch(const std::exception& e)
        {
            std::cout << bcolor::BrightRed << fcolor::Yellow << "[ERROR]: " << 
                bcolor::Reset << fcolor::Red << e.what() << '\n' << fcolor::Reset;
        }
    }
}

void AssetParserManager::ParseFile(const fs::path& inputPath) const
{
    std::string extension = GetPathExtension(inputPath);
    fs::path outputPath;
    if(config.HasOutputDir())
        outputPath = ReplaceRootDirWithConfigOutputDir(inputPath);
    else
        outputPath = inputPath;
    
    auto find = parsersMap.find(extension);
    if(find != parsersMap.end())
    {
        parser::BaseParser* parser = find->second;

        outputPath.replace_extension(parser->GetOutputExtension());

        std::string inputFile  = inputPath.string();
        std::string outputFile = outputPath.string();
        if(fs::exists(outputPath))
        {
            auto inputTime  = fs::last_write_time(inputPath);
            auto outputTime = fs::last_write_time(outputPath);
            
            if(inputTime > outputTime)
            {
                parser->ParseFile(*this, inputPath.string(), extension, outputPath.string());
                std::cout << fcolor::BrightGreen << "\"" << inputFile 
                    << "\" parsed succesfully\n" << fcolor::Reset;
            }
            else
                std::cout << fcolor::Green << "Skipping \"" << inputFile 
                    << "\"\n" << fcolor::Reset;
        }
        else
        {
            parser->ParseFile(*this, inputFile, extension, outputFile);
            std::cout << fcolor::BrightGreen << "\"" << inputFile 
                    << "\" parsed succesfully\n" << fcolor::Reset;
        }
    }
    else
        throw std::runtime_error("Could not parse file: \"" + 
            inputPath.string() + "\". Unsuported file extensions: \"" + 
            extension + "\"");
}

void AssetParserManager::ParseConfigFile(const fs::path& path)
{
    std::ifstream f(path.string());
    json data = json::parse(f);
    f.close();

    if(data.is_object())
    {
        ParseConfigOutputPath(data);
        ParseConfigEndianness(data);
    }
}

void AssetParserManager::ParseConfigOutputPath(const json& data)
{
    if(!config.outputDir.empty())
        return;
    
    if(data.contains(CONFIG_OUTPUT_DIR_KEY))
    {
        auto& outputPath = data[CONFIG_OUTPUT_DIR_KEY];
        if(outputPath.is_string())
        {
            config.outputDir = fs::path { outputPath.get<std::string>() };
            config.outputDir.make_preferred();
        }
    }
}

void AssetParserManager::ParseConfigEndianness(const json& data)
{
    if(data.contains(CONFIG_ENDIAN_KEY))
    {
        auto& endian = data[CONFIG_ENDIAN_KEY];
        if(endian.is_string())
        {
            std::string value = endian.get<std::string>();

            if(value == "little")
                config.endianness = std::endian::little;
            else if(value == "big")
                config.endianness = std::endian::big;
        }
    }
}

std::string AssetParserManager::GetPathExtension(const fs::path& path)
{
    std::string extension = path.extension().string().substr(1);

    //set the extension to lower case
    std::transform(extension.begin(), extension.end(), extension.begin(), 
        [](char c) { return std::tolower(c); } );

    return extension;
}