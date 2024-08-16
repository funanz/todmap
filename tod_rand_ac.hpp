#pragma once
#include <cstdint>

class tod_rand_ac
{
public:
    using result_type = uint8_t;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return 255; }

private:
    result_type x;

public:
    explicit tod_rand_ac(result_type seed) {
        x = seed;
    }

    result_type operator ()() {
        auto a = x >> 7;
        auto b = x >> 4;
        x = (x << 1) | (~(a ^ b) & 1);

        return x;
    }
};
