#include "ArgumentParser.hpp"
#include <stdexcept>

ArgumentParser::ArgumentParser(int argc, char* argv[])
{
    ParseTokens(argc, argv);
}

const std::string& ArgumentParser::GetOptionValue(const std::string& option, 
    std::size_t index) const
{
    auto find = tokens.find(option);

    if(find != tokens.end())
    {
        if(index < find->second.size())
            return find->second[index];
    }

    throw std::runtime_error("Could not get option value of \"" + option + "\"");
}

const std::vector<std::string>& ArgumentParser::GetOptionValues(const std::string& option) const
{
    auto find = tokens.find(option);

    if(find != tokens.end())
        return find->second;

    throw std::runtime_error("Could not get option values of \"" + option + "\"");
}

const std::size_t ArgumentParser::GetOptionValueCount(const std::string& option) const
{
    auto find = tokens.find(option);

    if(find != tokens.end())
        return find->second.size();
    
    throw std::runtime_error("Could not get option value count of \"" + option + "\"");
}

void ArgumentParser::ParseTokens(int argc, char* argv[])
{
    int32_t index = 1;

    while(index < argc)
    {
        std::string arg = argv[index];

        if(arg.starts_with(TOKEN_CHARACTER))
        {
            std::vector<std::string> values = ParseTokenValues(index + 1, argc, argv);
            index += values.size();

            auto find = tokens.find(arg);
            if(tokens.contains(arg))
                find->second.insert(find->second.end(), values.begin(), values.end());
            else
                tokens.emplace(std::move(arg), std::move(values));
        }
        
        index++;
    }
}

std::vector<std::string> ArgumentParser::ParseTokenValues(int startIndex, int argc, char* argv[])
{
    std::vector<std::string> ret {};

    if(startIndex < argc)
    {
        std::string value = argv[startIndex];
        while(!value.starts_with(TOKEN_CHARACTER) && startIndex < argc)
        {
            ret.emplace_back(std::move(value));
            startIndex++;
            
            if(startIndex < argc)
                value = argv[startIndex];
        }
    }

    return ret;
}