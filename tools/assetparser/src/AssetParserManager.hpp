#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <concepts>
#include <algorithm>
#include <filesystem>
#include <unordered_map>
#include "./parsers/BaseParser.hpp"

class AssetParserManager
{
public:
    AssetParserManager() = default;
    AssetParserManager(AssetParserManager&& other) = default;
    AssetParserManager& operator=(AssetParserManager&& other) = default;
    AssetParserManager(const AssetParserManager& other) = delete;
    AssetParserManager& operator=(const AssetParserManager& other) = delete;

    void ParseFile(const std::filesystem::path& path) const;

    template<typename T, typename... TParams> requires std::is_base_of_v<BaseParser, T>
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

private:
    static std::string PathToString(const std::filesystem::path::string_type& str);

private:
    std::vector<std::unique_ptr<BaseParser>> parsers {};
    std::unordered_map<std::string, BaseParser*> parsersMap {};
};