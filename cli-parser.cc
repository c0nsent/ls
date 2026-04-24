#include "cli-parser.hpp"

#include <stdexcept>


namespace cli
{
    ParserConstructor &ParserConstructor::addOption(const Option &option)
    {
        if (not m_options.try_emplace(option.name, option).second)
        {
            throw std::runtime_error("option already exists");
        }

        return *this;
    }


    bool ParserConstructor::has(const std::string &optionName) const
    {
        return m_options.contains(optionName);
    }


    optVal_t ParserConstructor::at(const std::string &optionName) const
    {
        return m_options.at(optionName).value;
    }


    optVal_t ParserConstructor::operator[](const std::string &optionName)
    {
        return m_options[optionName].value;
    }


    void ParserConstructor::setValue(const std::string &option, bool value)
    {
        //std::holds_alternative<bool *>(m_options[option].value); //Заебашь проверку на тип
        m_options[option].value = value;
    }


    void ParserConstructor::setValue(const std::string &option, i32 value)
    {
        m_options[option].value = value;
    }


    OptionType ParserConstructor::getType(const std::string &optionName) const
    {
        return m_options.at(optionName).type;
    }


    Parser::Parser(const i32 argc, const char *argv[], ParserConstructor &options)
        : m_arguments{argv + 1, argv + argc - 1}

    {
        for (u32 i{0}; i != m_arguments.size() ; ++i)
        {
            if (options.has(m_arguments[i]))
            {
                switch (options.getType(m_arguments[i]))
                {
                    case OptionType::Boolean:
                        options.setValue(m_arguments[i], true);
                        break;
                    case OptionType::Integer:
                        if (i + 1 >= argc)
                            throw std::runtime_error{"No value provided"};

                        options.setValue(m_arguments[i], std::stoi(m_arguments[++i]));
                        break;
                    default:
                        throw std::runtime_error("Unknown option type");
                }
            }
            else
                throw std::runtime_error{"Блядь"};
        }
    }
}
