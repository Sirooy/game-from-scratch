#include "ArgumentParser.hpp"
#include "AssetParserManager.hpp"
#include "./parsers/ImageParser.hpp"

int main(int argc, char* argv[])
{
    ArgumentParser args(argc, argv);
    AssetParserManager apm;
    apm.RegisterParser<ImageParser>();

    if(args.HasOption("-f") && args.GetOptionValueCount("-f") == 1)
    {
        apm.ParseFile(args.GetOptionValue("-f"));
    }
    else if(args.HasOption("-config"))
    {

    }
    else
        throw std::runtime_error("Invalid number of arguments");
}