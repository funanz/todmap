#pragma once
#include <cassert>
#include <cstdint>
#include <functional>
#include <tuple>
#include "tod_map.hpp"
#include "tod_rand_ac.hpp"

using tod_map_ac = tod_map<17*2+3, 8*2+3>;

class tod_map_builder_ac
{
    using progress_fn_t = std::function<void(const tod_map_ac&)>;
    progress_fn_t progress_fn;

public:
    tod_map_builder_ac() {
        progress_fn = [](auto&) {};
    }

    tod_map_ac build(int floor) {
        tod_rand_ac rng(to_seed(floor));

        return build(rng);
    }

    template <class RNG>
    tod_map_ac build(RNG& rng) {
        tod_map_ac map;

        for (int x = map.width() - 3; x >= 0; x -= 2)
            for (int y = 2; y < map.height(); y += 2)
                build_wall(map, x, y, rng);

        return map;
    }

    void progress(progress_fn_t fn) {
        progress_fn = fn ? fn : [](auto&) {};
    }

private:
    static uint8_t to_seed(int floor) {
        if (floor < 1) return 255;
        if (floor >= 60) return 255;

        return floor - 1;
    }

    template <class RNG>
    void build_wall(tod_map_ac& map, int x, int y, RNG& rng) {
        while (map.get(x, y) == Block::None) {
            map.set(x, y, Block::Piller);
            progress_fn(map);

            auto direction = rng() % 4;
            auto [wx, wy] = move(x, y, direction, 1);

            while (map.get(wx, wy) != Block::None) {
                direction = rng() % 4;
                std::tie(wx, wy) = move(x, y, direction, 1);
            }

            map.set(wx, wy, Block::Wall);
            progress_fn(map);

            std::tie(x, y) = move(x, y, direction, 2);
        }
    }

    static std::tuple<int, int> move(int x, int y, int direction, int length) {
        switch (direction) {
        case 0: return { x, y - length };
        case 1: return { x + length, y };
        case 2: return { x, y + length };
        case 3: return { x - length, y };
        }
        assert(0);
    }
};
