#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>


#include "basic-types-aliases.hpp"


namespace cli
{
    enum class OptionType : u8
    {
        Boolean,
        Integer,
        String,
    };


    struct Option
    {
        std::string name;
        std::string description;
        bool required = false;
        OptionType type;

        std::variant<bool *, i32 *, const char *> value;
    };


    class Options
    {

    public:

        Options() = default;

        Options &addOption(const Option &option);

    private:

        std::unordered_map<std::string, Option> m_options;
    };

    class Parser
    {

    public:

        Parser(i32 argc, const char *argv[], const Options &options);


    private:

        Options m_options;
        std::vector<std::string> m_arguments;
    };
}
