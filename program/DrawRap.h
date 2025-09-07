#pragma once
#include<string>
#include<DxLib.h>


namespace DxlibRap {
    class TextRenderer {
    public:
        // ’†‰›‚¼‚ë‚¦”Å DrawString
        inline static void CenterString(int x, int y, unsigned int color, const std::string& text) {
            // •E‚‚³‚ğæ“¾
            int textWidth = GetDrawStringWidth(text.c_str(), static_cast<int>(text.size()));
            int textHeight = GetFontSize();

            // ’†‰›À•W‚ğŒvZ
            int drawX = x - textWidth / 2;
            int drawY = y - textHeight / 2;

            // •`‰æ
            DrawString(drawX, drawY, text.c_str(), color);
        }
    };
}
