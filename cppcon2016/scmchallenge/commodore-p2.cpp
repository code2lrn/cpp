//
// Created by Ranga on 9/21/16.
//

#include <cstdint>
#include <algorithm>
#include <array>

namespace {
    struct Color {
        uint8_t num;
        uint8_t r;
        uint8_t g;
        uint8_t b;
        double luma = 0.2126 * r + 0.7152 * g + 0.0722 * b;
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

    template<typename Colors>
    constexpr auto sort_by_luma(const Colors &colors) -> decltype( colors ) {
        // Your job:
        // Using this formula: http://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color#596243
        // Y = 0.2126 R + 0.7152 G + 0.0722 B
        // The luma has been set in the color object as Color.luma for you. Now sort the `colors` parameter by .luma
        // in a constexpr enabled way, and return the newly sorted color data.
        decltype( colors ) sorted = colors;
        for( size_t i = 0; i < colors.size() - 1; ++i ) {
            bool no_swaps = true;
            for( size_t j = i + 1; j < colors.size(); ++j ) {
                if( sorted[ i ].luma > sorted[ j ].luma ) {
                    Color tmp = sorted[ i ];
                    sorted[ i ] = sorted[ j ];
                    sorted[ j ] = tmp;
                    no_swaps = false;
                }
            }
            if( no_swaps )
                break;
        }
        return sorted;
    }
}

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

    static_assert(12 == nearest_color<128, 128, 128>(colors).num, "");
    static_assert(0 == nearest_color<0, 0, 0>(colors).num, "");

    // Using this formula: http://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color#596243
    // Y = 0.2126 R + 0.7152 G + 0.0722 B
    // perform a compile-time sorting of the color data such that
    constexpr auto sorted_colors = sort_by_luma(colors);

    //static_assert(sorted_colors[0].num == 0, "");
    //static_assert(sorted_colors[7].num == 14, "");
    //static_assert(sorted_colors[8].num == 12, "");
    //static_assert(sorted_colors[15].num == 1, "");
}
