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
        //EnumSize, //Всегда должен быть последним
    };

    using optVal_t = std::variant<bool, i32>;

    struct Option
    {
        std::string name;
        std::string description;
        OptionType type;

        optVal_t value;
    };

    class Options
    {

    };

    class ParserConstructor
    {

    public:

        ParserConstructor() = default;


        ParserConstructor &addOption(const Option &option);

        bool has(const std::string &optionName) const;

        optVal_t at(const std::string &optionName) const;
        optVal_t operator[](const std::string &optionName);

        void setValue(const std::string &option, bool value);
        void setValue(const std::string &option, i32 value);
        //void setValue(const std::string &optionName, const char *value);


        OptionType getType(const std::string &optionName) const;

        std::string m_helpMessage;
        std::unordered_map<std::string, Option> m_options;
    };

    class Parser
    {
        friend class ParserConstructor;

        Parser(i32 argc, const char *const argv[], ParserConstructor &options);

        void constructHelp();

    public:



    private:

        Options m_options;
        std::vector<std::string> m_arguments;
    };
}
