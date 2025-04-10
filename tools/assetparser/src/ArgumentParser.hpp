#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

class ArgumentParser
{
public:
    using TokenMap = std::unordered_map<std::string, std::vector<std::string>>;

    inline static constexpr char TOKEN_CHARACTER {'-'};

    ArgumentParser(int argc, char* argv[]);
    ArgumentParser(ArgumentParser&& other) = default;
    ArgumentParser& operator=(ArgumentParser&& other) = default;
    ArgumentParser(const ArgumentParser& other) = delete;
    ArgumentParser& operator=(const ArgumentParser& other) = delete;

    const std::string& GetOptionValue(const std::string& option, std::size_t index = 0) const;
    const std::vector<std::string>& GetOptionValues(const std::string& option) const;
    std::size_t GetOptionValueCount(const std::string& option) const;

    bool HasOption(const std::string& option) const { return tokens.contains(option); }
    TokenMap::iterator Begin()             { return tokens.begin(); }
    TokenMap::iterator End()               { return tokens.end();   }
    TokenMap::const_iterator Begin() const { return tokens.begin(); }
    TokenMap::const_iterator End()   const { return tokens.end();   }

private:
    void ParseTokens(int argc, char* argv[]);
    std::vector<std::string> ParseTokenValues(int startIndex, int argc, char* argv[]);

private:
    TokenMap tokens {};
};