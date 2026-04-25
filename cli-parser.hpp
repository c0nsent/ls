#pragma once

#include <string>
#include <unordered_map>
#include <variant>

#include "basic-types-aliases.hpp"


namespace cli
{
    using optVal_t = std::variant<bool, i32>;
    using optName_t = std::string;

    class Options
    {

    public:

        enum class Type
        {
            Boolean,
            Integer,
        };

        struct Value
        {
            Type type;
            optVal_t defaultValue;
        };

        Options() = default;
        Options(Options &&) noexcept = default;

        Options &addOption(optName_t name, bool defaultValue);
        Options &addOption(optName_t name, i32 defaultValue);

        Type type(optName_t name) const;

        bool has(std::string_view name) const;
        optVal_t get(std::string_view name) const;

    private:

        std::unordered_map<optName_t, Value> m_options;
    };

    class Parser
    {
    public:

        Parser(i32 argc, const char *argv[], Options &&defaultOptions);

        optVal_t get(optName_t name) const;
        size_t argsCount() const;

    private:

        const Options m_defaultOptions;
        std::unordered_map<optName_t, Options::Value> m_parserOptions;
    };
}