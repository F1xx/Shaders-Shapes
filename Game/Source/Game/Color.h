#pragma once

class Color
{
public:
    Color() { r = 255; g = 255; b = 255; a = 255; };
    Color(unsigned char ar, unsigned char ag, unsigned char ab, unsigned char aa) { r = ar; g = ag; b = ab; a = aa; }

    unsigned char r, g, b, a;
};

namespace COLOR
{
    const Color Red = Color(255, 0, 0, 255);
    const Color Green = Color(0, 255, 0, 255);
    const Color Blue = Color(0, 0, 255, 255);
    const Color White = Color(255, 255, 255, 255);
    const Color Black = Color(0, 0, 0, 255);
    const Color Magenta = Color(255, 0, 255, 255);
    const Color Violet = Color(238, 130, 238, 255);
    const Color RoyalPurple = Color(120, 81, 169, 255);
}