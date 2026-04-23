#include "cli-parser.hpp"

#include <complex>
#include <stdexcept>


auto CliParser::toFlag(const std::string &flag) noexcept -> Flag
{
    if (flag == "-1")
        return Flag::OnePerLine;

    if (flag == "--help" or flag == "-h")
        return Flag::Help;

    return Flag::Undefined;
}


CliParser::CliParser(const i32 argc, const char *argv[])
{
    //argv+1, потому что название программы не нужно
    std::vector<std::string> args{argv + 1, argv + argc - 1};

    for (u32 i{0}; i < argc; ++i)
    {
        const auto flag{toFlag(args[i])};

        if (flag == Flag::Undefined)
            throw std::logic_error("Undefined flag");

        if (not m_args.try_emplace(flag, args[++i]).second)
            throw std::logic_error("Duplicate flag");


    }

}


auto CliParser::has(Flag flag) const noexcept -> bool
{

}
auto CliParser::getString(Flag flag) const noexcept -> std::optional<std::string> {}
auto CliParser::getBool(Flag flag) const noexcept -> std::optional<bool> {}
auto CliParser::getInt(Flag flag) const noexcept -> std::optional<int> {}


auto CliParser::get(Flag flag) const -> std::string
{

}
