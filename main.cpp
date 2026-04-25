#include "cli-parser.hpp"

#include <print>


int main(const i32 argc, const char * argv[])
{
    cli::Options options;

    options.addOption("-1", false);

    /*
    std::array args{"ls", "-1"};

    cli::Parser parser{args.size(), args.data(), std::move(options)};
    */

    cli::Parser parser{argc, argv, std::move(options)};

    if (std::get<bool>(parser.get("-1")))
        std::println("test");
}