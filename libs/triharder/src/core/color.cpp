#include <iomanip>
#include <sstream>
#include "color.h"

namespace TriHarder {
    Color Color::fromBytes(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        return Color{
                static_cast<float>(r) / 255.0f,
                static_cast<float>(g) / 255.0f,
                static_cast<float>(b) / 255.0f,
                static_cast<float>(a) / 255.0f
        };
    }

    Color Color::fromHex(const TriHarder::String &hex) {
        // Trim the leading '#' if present
        String hexTrimmed = hex;
        if (hexTrimmed[0] == '#') {
            hexTrimmed = hexTrimmed.substr(1);
        }

        // Ensure the hex code is 6 or 8 characters long
        if (hexTrimmed.length() != 6 && hexTrimmed.length() != 8) {
            throw ColorError("Invalid hex code length");
        }

        // Convert the hex code to a 32-bit integer
        uint32_t hexInt = std::strtoul(hexTrimmed.c_str(), nullptr, 16);

        // Extract the red, green, blue, and alpha values
        uint8_t r, g, b, a;
        if (hexTrimmed.length() == 8) {
            r = (hexInt >> 24) & 0xFF;
            g = (hexInt >> 16) & 0xFF;
            b = (hexInt >> 8) & 0xFF;
            a = hexInt & 0xFF;
        } else {
            r = (hexInt >> 16) & 0xFF;
            g = (hexInt >> 8) & 0xFF;
            b = hexInt & 0xFF;
            a = 0xFF;  // Default alpha value for 6-character hex
        }

        return fromBytes(r, g, b, a);
    }

    String Color::toHex() const {
        auto to_hex_component = [](float component) -> String {
            auto value = static_cast<uint8_t>(std::round(component * 255.0f));
            std::ostringstream oss;
            oss << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<int>(value);
            return oss.str();
        };

        String hex = "#" + to_hex_component(r) + " " + to_hex_component(g) + " " + to_hex_component(b);
        if (a < 1.0f) {
            hex += to_hex_component(a);
        }

        return hex;
    }

    std::array<uint8_t, 4> Color::toRgba() const {
        auto rr = static_cast<uint8_t>(std::round(this->r * 255.0));
        auto gg = static_cast<uint8_t>(std::round(this->g * 255.0));
        auto bb = static_cast<uint8_t>(std::round(this->b * 255.0));
        auto aa = static_cast<uint8_t>(std::round(this->a * 255.0));
        return {rr, gg, bb, aa};
    }

    Color Color::withAlpha(float alpha) const {
        auto color = *this;
        color.a = std::max(0.0f, std::min(alpha, 1.0f));
        return color;
    }

    void Color::normalize() {
        r = std::max(0.0f, std::min(r, 1.0f));
        g = std::max(0.0f, std::min(g, 1.0f));
        b = std::max(0.0f, std::min(b, 1.0f));
        a = std::max(0.0f, std::min(a, 1.0f));
    }
}
