#include <print>
#include <filesystem>

#include "basic-types-aliases.hpp"




int main(const i32 argc, char *argv[])
{
    namespace fs = std::filesystem;

    if (argc > 2)
    {
        std::println("Too many arguments.");
        return 1;
    }

    for (const auto &entry : fs::directory_iterator{fs::current_path()})
    {
        std::print("{} ", entry.path().filename().string());
    }
}