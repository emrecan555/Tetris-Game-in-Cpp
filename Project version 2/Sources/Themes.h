#pragma once
#include "colors.h"
class Themes {
public:
    Themes();
    void ApplyBackgroundcolor(int themeIndex);
    void ApplyTextcolor(int themeIndex);
    void ApplyBoxBackgroundcolor(int themeIndex);
    Color GetBackgroundColor(int themeIndex);
    Color GetBoxBackgroundColor(int themeIndex);
    Color GetTextColor(int themeIndex);
    Color backgroundcolor;
    Color textcolor;
    Color boxbackgroundcolor;
    std::vector<Color> backgroundColors;
    std::vector<Color> textColors;
    std::vector<Color> boxbackgroundColors;
private:
    
};