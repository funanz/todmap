#include <cctype>
#include <chrono>
#include <cstdio>
#include <map>
#include <string>
#include <thread>
#include "tod_map_builder_ac.hpp"
#include "tod_map_builder_fc.hpp"

static const std::map<std::string, std::string> char_map = {
    { "wall", "\U0001f7eb" }, // brown square
    { "floor", "\U0001f9f1" }, // brick
};

template <class T>
concept MapBuilder = requires (T& mb) { mb.build(1); };

template <MapBuilder T>
static void print_map(T& mb, int floor, bool progress)
{
    if (progress) {
        mb.progress([](auto& map) {
            map.print(char_map);
            printf("\x1b[%dA", map.height());

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        });
    }

    auto map = mb.build(floor);
    map.print(char_map);
}

static void print_map(const std::string& mode, int floor, bool progress)
{
    printf("Mode=%s Floor=%d\n", mode.c_str(), floor);

    if (mode == "AC") {
        tod_map_builder_ac mb;
        print_map(mb, floor, progress);
    }
    else if (mode == "FC") {
        tod_map_builder_fc mb;
        print_map(mb, floor, progress);
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
    bool progress = false;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--ac" || arg == "-a")
            mode = "AC";
        else if (arg == "--fc" || arg == "-f")
            mode = "FC";
        else if (arg == "--progress" || arg == "-p")
            progress = true;
        else if (arg == "--no-progress" || arg == "-P")
            progress = false;
        else if (is_number(arg))
            print_map(mode, std::stoi(arg), progress);
    }
}
