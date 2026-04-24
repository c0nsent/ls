#include "cli-parser.hpp"


int main(i32 argc, const char *const argv[])
{
    cli::ParserConstructor lsOptions;

    lsOptions.addOption({
        .name = "-1",
        .description = "",
        .type = cli::OptionType::Boolean,
        .value = false,
    });

    cli::Parser parser{argc, argv, lsOptions};

    parser.

}