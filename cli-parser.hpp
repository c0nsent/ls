#pragma once

#include <limits>
#include <optional>

#include "basic-types-aliases.hpp"

#include <string>
#include <unordered_map>
#include <span>
#include <vector>

enum Flag : u8
{
    Help,
    OnePerLine,
    Undefined = std::numeric_limits<u8>::max(),
};


class CliParser
{
    static auto toFlag(const std::string &flag) noexcept -> Flag;


public:

    CliParser(i32 argc, const char *argv[]);
    auto has(Flag flag) const noexcept -> bool;
    auto getString(Flag flag) const noexcept -> std::optional<std::string>;
    auto getBool(Flag flag) const noexcept -> std::optional<bool>;
    auto getInt(Flag flag) const noexcept -> std::optional<int>;


private:

    std::unordered_map<Flag, std::string> m_args;
};