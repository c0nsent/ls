#include "cli-parser.hpp"

#include <stdexcept>


namespace cli
{
    Options & Options::addOption(const Option &option)
    {
        if (not m_options.try_emplace(option.name, option).second)
        {
            throw std::runtime_error("option already exists");
        }

        return *this;
    }

    Parser::Parser(const i32 argc, const char *argv[], const Options &options)
        : m_options(options)
    {
        m_arguments.reserve(argc - 1);

        for (u32 i{1}; i < argc; ++i)
        {
            m_arguments.push_back(argv[i]);
        }

        for (u32 i{0}; i != m_arguments.size() ; ++i)
        {

        }
    }
}
