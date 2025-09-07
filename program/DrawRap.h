#pragma once
#include<string>
#include<DxLib.h>


namespace DxlibRap {
    class TextRenderer {
    public:
        // �������낦�� DrawString
        inline static void CenterString(int x, int y, unsigned int color, const std::string& text) {
            // ���E�������擾
            int textWidth = GetDrawStringWidth(text.c_str(), static_cast<int>(text.size()));
            int textHeight = GetFontSize();

            // �������W���v�Z
            int drawX = x - textWidth / 2;
            int drawY = y - textHeight / 2;

            // �`��
            DrawString(drawX, drawY, text.c_str(), color);
        }
    };
}
