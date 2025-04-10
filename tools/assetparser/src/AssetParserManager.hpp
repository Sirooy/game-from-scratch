#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <concepts>
#include <algorithm>
#include <filesystem>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "./parsers/BaseParser.hpp"

class AssetParserManager
{
public:
    struct Configuration
    {
        std::filesystem::path rootDir   { };
        std::filesystem::path outputDir { };
        std::endian endianness          { std::endian::little };

        bool HasOutputDir() const { return !outputDir.empty(); }
    };

    AssetParserManager() = default;
    AssetParserManager(AssetParserManager&& other) = default;
    AssetParserManager& operator=(AssetParserManager&& other) = default;
    AssetParserManager(const AssetParserManager& other) = delete;
    AssetParserManager& operator=(const AssetParserManager& other) = delete;

    void ParseSingleFile(std::filesystem::path path) const;
    void ParseDirectory(std::filesystem::path rootDirectory);
    void SetOutputDirectory(std::filesystem::path outputDir);

    template<typename T, typename... TParams> requires std::is_base_of_v<parser::BaseParser, T>
    void RegisterParser(TParams&&... params)
    {
        auto& parser           = parsers.emplace_back(std::make_unique<T>(std::forward<TParams>(params)...));
        const auto& extensions = parser->GetInputExtensions();

        for(const auto& extension : extensions)
        {
            if(parsersMap.contains(extension)) 
                throw std::runtime_error("Could not add parser. Extension \"" + extension + "\" has already been added");
            
            parsersMap.emplace(extension, parser.get());
        }
    }

    const Configuration& Config() const { return config; }

private:
    using FilesAndDirectories = std::tuple<std::vector<std::filesystem::path>, 
        std::vector<std::filesystem::path>>;
    
    FilesAndDirectories GetFilesAndDirectories(const std::filesystem::path& rootDirectory, 
        const std::filesystem::path& configPath);
    void CreateDirectories(const std::vector<std::filesystem::path> directories);
    void ParseFiles(const std::vector<std::filesystem::path>& files);
    void ParseFile(const std::filesystem::path& inputPath) const;
    void ParseConfigFile(const std::filesystem::path& path);
    void ParseConfigOutputPath(const nlohmann::json& data);
    void ParseConfigEndianness(const nlohmann::json& data);
    std::filesystem::path ReplaceRootDirWithConfigOutputDir(const std::filesystem::path& path) const;
    
    static std::string GetPathExtension(const std::filesystem::path& path);

private:
    std::vector<std::unique_ptr<parser::BaseParser>> parsers {};
    std::unordered_map<std::string, parser::BaseParser*> parsersMap {};
    Configuration config {};
};