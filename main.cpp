#include <cctype>
#include <cstdio>
#include <map>
#include <string>
#include "tod_map_builder_ac.hpp"
#include "tod_map_builder_fc.hpp"

static const std::map<std::string, std::string> char_map = {
    { "wall", "\U0001f7eb" }, // brown square
    { "floor", "\U0001f9f1" }, // brick
};

static void print_map(const std::string& mode, int floor)
{
    printf("Mode=%s Floor=%d\n", mode.c_str(), floor);

    if (mode == "AC") {
        tod_map_builder_ac mb;
        auto map = mb.build(floor);
        map.print(char_map);
    }
    else if (mode == "FC") {
        tod_map_builder_fc mb;
        auto map = mb.build(floor);
        map.print(char_map);
    }
}

static bool is_number(const std::string& s)
{
    for (auto c : s) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    std::string mode = "AC";

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--ac")
            mode = "AC";
        else if (arg == "--fc")
            mode = "FC";
        else if (is_number(arg))
            print_map(mode, std::stoi(arg));
    }
}
