#include <iostream>
#include "Color.hpp"
#include "ArgumentParser.hpp"
#include "AssetParserManager.hpp"
#include "./parsers/ImageParser.hpp"


int main(int argc, char* argv[])
{
    ArgumentParser args(argc, argv);
    AssetParserManager apm;
    apm.RegisterParser<parser::ImageParser>();
    
    try
    {
        if(args.HasOption("-f") && args.GetOptionValueCount("-f") == 1)
        {
            apm.ParseSingleFile(args.GetOptionValue("-f"));
        }
        else if(args.HasOption("-d") && args.GetOptionValueCount("-d") == 1)
        {
            apm.ParseDirectory(args.GetOptionValue("-d"));
        }
        else
            throw std::runtime_error("Invalid number of arguments");
    }
    catch(const std::exception& e)
    {
        std::cout << bcolor::BrightRed << fcolor::Yellow << "[ERROR]: " << 
            bcolor::Reset << fcolor::Red << e.what() << '\n' << fcolor::Reset;
    }
}