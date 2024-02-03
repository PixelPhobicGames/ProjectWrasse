
#include <cstring>
#include <cstdlib>

#include "raygui.h"

static const GuiStyleProp StyleProps[22] = {
    { 0, 0, 0xFF0000FF },    // DEFAULT_BORDER_COLOR_NORMAL (Red)
    { 0, 1, 0x00FF00FF },    // DEFAULT_BASE_COLOR_NORMAL (Green)
    { 0, 2, 0x0000FFFF },    // DEFAULT_TEXT_COLOR_NORMAL (Blue)
    { 0, 3, 0xFF00FFFF },    // DEFAULT_BORDER_COLOR_FOCUSED (Magenta)
    { 0, 4, 0xFFFF00FF },    // DEFAULT_BASE_COLOR_FOCUSED (Yellow)
    { 0, 5, 0xFF7F00FF },    // DEFAULT_TEXT_COLOR_FOCUSED (Orange)
    { 0, 6, 0x800080FF },    // DEFAULT_BORDER_COLOR_PRESSED (Purple)
    { 0, 7, 0x008080FF },    // DEFAULT_BASE_COLOR_PRESSED (Teal)
    { 0, 8, 0xFF007FFF },    // DEFAULT_TEXT_COLOR_PRESSED (Pink)
    { 0, 9, 0x808080FF },    // DEFAULT_BORDER_COLOR_DISABLED (Gray)
    { 0, 10, 0xC0C0C0FF },   // DEFAULT_BASE_COLOR_DISABLED (Silver)
    { 0, 11, 0x996633FF },   // DEFAULT_TEXT_COLOR_DISABLED (Brown)
    { 0, 16, 0x00000010 },   // DEFAULT_TEXT_SIZE (Not related to color)
    { 0, 17, 0x00000000 },   // DEFAULT_TEXT_SPACING (Not related to color)
    { 0, 18, 0xFF00A5FF },   // DEFAULT_LINE_COLOR (Vibrant Pink)
    { 0, 19, 0x800000FF },   // DEFAULT_BACKGROUND_COLOR (Dark Red)
    { 1, 5, 0xFFD700FF },    // LABEL_TEXT_COLOR_FOCUSED (Gold)
    { 1, 8, 0xFF1493FF },    // LABEL_TEXT_COLOR_PRESSED (Deep Pink)
    { 4, 5, 0x9932CCFF },    // SLIDER_TEXT_COLOR_FOCUSED (Dark Orchid)
    { 5, 5, 0x8A2BE2FF },    // PROGRESSBAR_TEXT_COLOR_FOCUSED (Blue Violet)
    { 9, 5, 0xFF4500FF },    // TEXTBOX_TEXT_COLOR_FOCUSED (Orange Red)
    { 10, 5, 0x7B68EEFF },   // VALUEBOX_TEXT_COLOR_FOCUSED (Medium Slate Blue)
};

static void GuiLoadStyle(void)
{
    for (int i = 0; i < 22; i++)
    {
        GuiSetStyle(StyleProps[i].controlId, StyleProps[i].propertyId, StyleProps[i].propertyValue);
    }

    Font font = LoadFont("GameData/Global/GuiFont.ttf");

    GuiSetFont(font);

}
