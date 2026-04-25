#include "cli-parser.hpp"

#include <stdexcept>
#include <vector>


namespace cli
{
    Options &Options::addOption(optName_t name, bool defaultValue)
    {
        if (not m_options.try_emplace(name, Value{.type = Type::Boolean, .defaultValue = defaultValue}).second)
            throw std::logic_error("Option \"" + name + "\" already exists");

        return *this;
    }

    Options &Options::addOption(optName_t name, i32 defaultValue)
    {
        if (not m_options.try_emplace(std::move(name), Value{.type = Type::Integer, .defaultValue = defaultValue}).second)
           throw std::logic_error("Option \"" + name + "\" already exists");

        return *this;
    }


    Options::Type Options::type(optName_t name) const
    {
        return m_options.at(name).type;
    }


    bool Options::has(std::string_view name) const
    {
        return m_options.contains(optName_t(name));
    }


    optVal_t Options::get(std::string_view name) const
    {
        if (m_options.contains(optName_t(name)))
            return m_options.at(optName_t(name)).defaultValue;

        throw std::logic_error("Option \"" + optName_t(name) + "\" does not exists");
    }


    Parser::Parser(const i32 argc, const char *argv[], Options &&defaultOptions)
        : m_defaultOptions{std::move(defaultOptions)}
    {
        if (argc < 2) return;


        std::vector<optName_t> args{*argv, *(argv + argc - 1)};

        for (size_t i{1}; i != args.size(); ++i) //игрорируем название самой проги
        {
            if (m_defaultOptions.has(args[i]))
            {
                if (Options::Type::Boolean == m_defaultOptions.type(args[i]))
                {
                    m_parserOptions.emplace(args[i], Options::Value{.type = Options::Type::Boolean, .defaultValue = true} );
                }
                else if (Options::Type::Integer == m_defaultOptions.type(args[i]))
                {
                    m_parserOptions.emplace(args[i], Options::Value{.type = Options::Type::Integer, .defaultValue = std::stoi(args[++i])} );
                }
            }
        }
    }
    optVal_t Parser::get(optName_t name) const
    {
        if (m_parserOptions.contains(name))
            return m_parserOptions.at(name).defaultValue;

        throw std::runtime_error("Option \"" + name + "\" does not exists");
    }


    size_t Parser::argsCount() const
    {
        return m_parserOptions.size();
    }
}
