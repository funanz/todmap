#pragma once
#include <cstdint>

enum class Block : uint8_t {
    None = 0,
    OuterWall = 1,
    Piller = 2,
    Wall = 3,
    OutOfRange = 255,
};

template <int Width, int Height>
class tod_map {
    Block map[Height][Width];

public:
    tod_map() {
        fill();
    }

    static constexpr int width() { return Width; };
    static constexpr int height() { return Height; };

    void fill() {
        for (int y = 0; y < Height; y++) {
            for (int x = 0; x < Width; x++) {
                if (x == 0 || x == Width-1 || y == 0 || y == Height-1)
                    map[y][x] = Block::OuterWall;
                else
                    map[y][x] = Block::None;
            }
        }
    }

    Block get(int x, int y) const {
        if (!check_boundary(x, y)) return Block::OutOfRange;

        return map[y][x];
    }

    bool set(int x, int y, Block block) {
        if (!check_boundary(x, y)) return false;

        map[y][x] = block;
        return true;
    }

    bool check_boundary(int x, int y) const {
        if (x < 0 || x >= Width) return false;
        if (y < 0 || y >= Height) return false;
        return true;
    }

    template<class Map>
    void print(const Map& char_map) const {
        auto wall = char_map.at("wall").c_str();
        auto floor = char_map.at("floor").c_str();

        for (int y = 0; y < Height; y++) {
            for (int x = 0; x < Width; x++) {
                printf("%s", map[y][x] == Block::None ? floor : wall);
            }
            printf("\n");
        }
    }
};
