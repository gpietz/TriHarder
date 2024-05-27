#pragma once

#include "../triharder.h"
#include <array>

namespace TriHarder {

    class ColorError : public std::runtime_error {
    public:
        explicit ColorError(const String &msg) : std::runtime_error(msg) {}
    };

    class Color {
    public:
        float r;
        float g;
        float b;
        float a;

        /**
         * @brief Constructs a color from RGBA bytes.
         *
         * This static method constructs a color object from the given RGBA bytes.
         *
         * @param r The red component of the color.
         * @param g The green component of the color.
         * @param b The blue component of the color.
         * @param a The alpha component of the color.
         *
         * @return A color object with the specified RGBA components.
         */
        static Color fromBytes(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        static Color fromHex(const String &hex);

        [[nodiscard]] String toHex() const;

        [[nodiscard]] std::array<uint8_t , 4> toRgba() const;

        [[nodiscard]] Color withAlpha(float alpha) const;

        void normalize();
    };
}
