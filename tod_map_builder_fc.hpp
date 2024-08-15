#pragma once
#include <cassert>
#include <cstdint>
#include <set>
#include <tuple>
#include "tod_map.hpp"
#include "tod_rand_fc.hpp"

using tod_map_fc = tod_map<15*2+3, 6*2+3>;

class tod_map_builder_fc
{
public:
    tod_map_fc build(int floor) {
        if (1 <= floor && floor <= 59) {
            auto [s1, s2] = to_seed(floor);
            tod_rand_fc rng(s1, s2);

            return build(rng);
        } else {
            tod_rand_fc_floor60 rng;

            return build(rng);
        }
    }

private:
    static std::tuple<uint8_t, uint8_t> to_seed(int floor) {
        auto x = floor * 3 + 3;

        return { x, x + 2 };
    }

    template <class RNG>
    tod_map_fc build(RNG& rng) {
        tod_map_fc map;

        for (int y = 2; y < map.height(); y += 2)
            for (int x = 2; x < map.width(); x += 2)
                build_wall(map, x, y, rng);

        return map;
    }

    template <class RNG>
    void build_wall(tod_map_fc& map, int x, int y, RNG& rng) {
        std::set<std::tuple<int, int>> history;

        while (map.get(x, y) == Block::None) {
            map.set(x, y, Block::Piller);
            history.insert({x, y});

            // Is it closed in history?
            if (history.contains(move(x, y, 0, 2)) &&
                history.contains(move(x, y, 1, 2)) &&
                history.contains(move(x, y, 2, 2)) &&
                history.contains(move(x, y, 3, 2))) {
                break;
            }

            for (;;) {
                auto direction = rng() % 4;

                auto [nx, ny] = move(x, y, direction, 2);
                if (history.contains({nx, ny}))
                    continue;

                auto [wx, wy] = move(x, y, direction, 1);
                if (map.get(wx, wy) != Block::None)
                    continue;

                map.set(wx, wy, Block::Wall);
                x = nx;
                y = ny;
                break;
            }
        }
    }

    static std::tuple<int, int> move(int x, int y, int direction, int length) {
        switch (direction) {
        case 0: return { x, y - length };
        case 1: return { x, y + length };
        case 2: return { x - length, y };
        case 3: return { x + length, y };
        }
        assert(0);
    }
};