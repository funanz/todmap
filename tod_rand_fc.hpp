#pragma once
#include <cstdint>

class tod_rand_fc
{
public:
    using result_type = uint8_t;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return 255; }

private:
    result_type x;
    result_type y;

public:
    tod_rand_fc(result_type seed1, result_type seed2) {
        x = seed1;
        y = seed2;
    }

    result_type operator ()() {
        auto a = x >> 7;
        auto b = x >> 4;
        x = (x << 1) | (~(a ^ b) & 1);

        y = y * 5 + 1;

        return x ^ y;
    }
};

class tod_rand_fc_floor60
{
public:
    using result_type = uint8_t;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return 255; }

    result_type operator ()() { return 2; }
};
