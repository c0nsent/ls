#include "cli-parser.hpp"

#include <stdexcept>
#include <vector>


namespace cli
{
    Options &Options::addOption(optName_t name, bool defaultValue)
    {
        if (not m_options.contains(name))
        {
            m_options.emplace(std::move(name), Value{.type = Type::Boolean, .defaultValue = defaultValue} );
            return *this;
        }

        throw std::logic_error("Option \"" + name + "\" already exists");
    }

    Options &Options::addOption(optName_t name, i32 defaultValue)
    {
        if (not m_options.contains(name))
        {
            m_options.emplace(std::move(name), Value{.type = Type::Integer, .defaultValue = defaultValue} );
            return *this;
        }

        throw std::logic_error("Option \"" + name + "\" does not exists");
    }


    Options::Type Options::type(const optName_t &name) const
    {
        return m_options.at(name).type;
    }


    bool Options::has(const optName_t &name) const
    {
        return m_options.contains(name);
    }


    optVal_t Options::get(const optName_t &name) const
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
            auto &name{args[i]};

            if (not m_defaultOptions.has(name)) continue;

            Options::Value value{};

            switch (m_defaultOptions.type(name))
            {
                using enum Options::Type;

                case Boolean:
                    value = {.type = Boolean, .defaultValue = true};
                    break;
                case Integer:
                    value = {.type = Integer, .defaultValue = std::stoi(args[++i])};
                    break;
            }

            m_parserOptions.emplace(std::move(name), value);
        }
    }


    optVal_t Parser::get(const optName_t &name) const
    {
        if (m_parserOptions.contains(name))
            return m_parserOptions.at(name).defaultValue;

        throw std::runtime_error("Option \"" + name + "\" does not exists");
    }


    size_t Parser::argsCount() const noexcept
    {
        return m_parserOptions.size();
    }
}
