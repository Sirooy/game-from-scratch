#include "ArgumentParser.hpp"
#include "AssetParserManager.hpp"
#include "./parsers/ImageParser.hpp"

int main(int argc, char* argv[])
{
    ArgumentParser args(argc, argv);
    AssetParserManager apm;
    apm.RegisterParser<parser::ImageParser>();

    if(args.HasOption("-f") && args.GetOptionValueCount("-f") == 1)
    {
        apm.ParseSingleFile(std::filesystem::directory_entry { args.GetOptionValue("-f") });
    }
    else if(args.HasOption("-d") && args.GetOptionValueCount("-d") == 1)
    {
        apm.ParseDirectory(args.GetOptionValue("-d"));
    }
    else
        throw std::runtime_error("Invalid number of arguments");
}