#pragma once
#include <cassert>
#include <cstdint>
#include "tod_map.hpp"
#include "tod_rand_ac.hpp"

using tod_map_ac = tod_map<17*2+3, 8*2+3>;

class tod_map_builder_ac
{
public:
    tod_map_ac build(int floor) {
        tod_rand_ac rng(to_seed(floor));

        return build(rng);
    }

private:
    static uint8_t to_seed(int floor) {
        if (floor < 1) return 255;
        if (floor >= 60) return 255;

        auto x = floor - 1;
        return (x << 1) + (~(x >> 4) & 1);
    }

    template <class RNG>
    tod_map_ac build(RNG& rng) {
        tod_map_ac map;

        for (int x = map.width() - 3; x >= 0; x -= 2)
            for (int y = 2; y < map.height(); y += 2)
                build_wall(map, x, y, rng);

        return map;
    }

    template <class RNG>
    void build_wall(tod_map_ac& map, int x, int y, RNG& rng) {
        while (map.get(x, y) == Block::None) {
            map.set(x, y, Block::Piller);

            for (;;) {
                auto direction = rng() % 4;

                auto [wx, wy] = move(x, y, direction, 1);
                if (map.get(wx, wy) != Block::None)
                    continue;

                map.set(wx, wy, Block::Wall);

                auto [nx, ny] = move(x, y, direction, 2);
                x = nx;
                y = ny;
                break;
            }
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
