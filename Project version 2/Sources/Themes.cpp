#include "Themes.h"

Themes::Themes()
{
    backgroundColors = { darkBlue,darkGreen, darklavender };
	backgroundcolor = darkBlue;
    boxbackgroundColors = { lightBlue,lightGreen,lavender };
    boxbackgroundcolor = lightBlue;
    textColors = { WHITE,BLACK,BLUE };
    textcolor = WHITE;
}

void Themes::ApplyBackgroundcolor(int themeIndex)
{
    switch (themeIndex) {
    case 0:
        backgroundcolor = GetBackgroundColor(0);
        break;
    case 1:
        backgroundcolor = GetBackgroundColor(1);
        break;
    case 2:
        backgroundcolor = GetBackgroundColor(2);
        break;
        // Diðer temalarý ekleyebilirsiniz.
    }
}
void Themes::ApplyTextcolor(int themeIndex)
{
    switch (themeIndex) {
    case 0:
        textcolor = GetTextColor(0);
        break;
    case 1:
        textcolor = GetTextColor(1);
        break;
    case 2:
        textcolor = GetTextColor(2);
        break;
        // Diðer temalarý ekleyebilirsiniz.
    }
}

void Themes::ApplyBoxBackgroundcolor(int themeIndex)
{
    switch (themeIndex) {
    case 0:
        boxbackgroundcolor = GetBoxBackgroundColor(0);
        break;
    case 1:
        boxbackgroundcolor = GetBoxBackgroundColor(1);
        break;
    case 2:
        boxbackgroundcolor = GetBoxBackgroundColor(2);
        break;
        // Diðer temalarý ekleyebilirsiniz.
    }
}

Color Themes::GetBackgroundColor(int themeIndex)
{
	return backgroundColors[themeIndex];
}

Color Themes::GetBoxBackgroundColor(int themeIndex)
{
    return boxbackgroundColors[themeIndex];
}

Color Themes::GetTextColor(int themeIndex)
{
    return textColors[themeIndex];
}
