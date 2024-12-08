#include "colors.h"

const Color darkGrey = { 26, 31, 40, 255 };
const Color red = { 255, 0, 0, 255 };
const Color green = { 0, 255, 0, 255 };
const Color blue = { 0, 0, 255, 255 };
const Color yellow = { 255, 255, 0, 255 };
const Color magenta = { 255, 0, 255, 255 };
const Color cyan = { 0, 255, 255, 255 };
const Color gray = { 128, 128, 128, 255 };
const Color orange = { 255, 165, 0, 255 };
const Color purple = { 128, 0, 128, 255 };
const Color teal = { 0, 128, 128, 255 };
const Color pink = { 255, 192, 203, 255 };
const Color brown = { 139, 69, 19, 255 };
const Color darkGreen = { 0, 128, 0, 255 };
const Color darkRed = { 128, 0, 0, 255 };
const Color lightBlue = { 59, 85, 162, 255 };
const Color darkBlue = { 44, 44, 127, 255 };
const Color lightGreen = { 144, 238, 144, 255 };
const Color lavender = { 230, 230, 250, 255 };
const Color darklavender = { 230, 230, 200, 255 };
std::vector<Color> GetCellColors()
{
    return { darkGrey, red, green, orange, yellow,magenta,cyan,gray,orange, purple,teal,pink,brown,darkRed, WHITE};
}

