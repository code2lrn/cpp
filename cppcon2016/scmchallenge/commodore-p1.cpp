//
// Created by Ranga on 9/21/16.
//

#include <cstdint>
#include <algorithm>
#include <array>
#include <iostream>

namespace {
    struct Color {
        uint8_t num;
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

// Make this constexpr
    template<typename T>
    constexpr auto square(T t) -> decltype(t) {
        return t * t;
    }

// Make this constexpr
    template<uint8_t r, uint8_t g, uint8_t b>
    constexpr bool color_comparison(const Color &lhs, const Color &rhs) {
        return (square(lhs.r - r) + square(lhs.g - g) + square(lhs.b - b))
               < (square(rhs.r - r) + square(rhs.g - g) + square(rhs.b - b));
    }

// Make this constexpr
    template<uint8_t r, uint8_t g, uint8_t b, typename Colors>
    constexpr auto nearest_color(const Colors &colors) -> decltype(colors[0]) {
        return *std::min_element(&(colors[0]), &(colors[16]), color_comparison<r, g, b>);
    }

};

int main() {
    constexpr std::array<Color, 16> colors{{
                                                   Color{0, 0x00, 0x00, 0x00},
                                                   Color{1, 0xFF, 0xFF, 0xFF},
                                                   Color{2, 0x88, 0x39, 0x32},
                                                   Color{3, 0x67, 0xB6, 0xBD},
                                                   Color{4, 0x8B, 0x3F, 0x96},
                                                   Color{5, 0x55, 0xA0, 0x49},
                                                   Color{6, 0x40, 0x31, 0x8D},
                                                   Color{7, 0xBF, 0xCE, 0x72},
                                                   Color{8, 0x8B, 0x54, 0x29},
                                                   Color{9, 0x57, 0x42, 0x00},
                                                   Color{10, 0xB8, 0x69, 0x62},
                                                   Color{11, 0x50, 0x50, 0x50},
                                                   Color{12, 0x78, 0x78, 0x78},
                                                   Color{13, 0x94, 0xE0, 0x89},
                                                   Color{14, 0x78, 0x69, 0xC4},
                                                   Color{15, 0x9F, 0x9F, 0x9F}
                                           }};
    // Your job:
    // Get these two static_assert statements compiling.
    static_assert(12 == nearest_color<128,128,128>(colors).num, "");
    static_assert(0 == nearest_color<0, 0, 0>(colors).num, "");
    //std::cout << nearest_color<128, 128, 128>(colors).num << '\n';
}

