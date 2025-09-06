#include "Color.h"
#include<cmath>
#include"DxLib.h"

/// <summary>
/// 色の中間色を取得してグラデーションにようにブレンドする
/// </summary>
/// <param name="arg_color1"> 最初の色 </param>
/// <param name="arg_color2"> 変えたい色 </param>
/// <param name="arg_colorLerp"> ブレンド割合 </param>
void color::Color::BlendColor(const Color& arg_color1, const Color& arg_color2, const float& arg_colorLerp)
{
	red_ = (int)std::lerp(arg_color1.red_, arg_color2.red_, arg_colorLerp);
	green_ = (int)std::lerp(arg_color1.green_, arg_color2.green_, arg_colorLerp);
	blue_ = (int)std::lerp(arg_color1.blue_, arg_color2.blue_, arg_colorLerp);
}

/// <summary>
/// クラス内の色を使って色コードを取得
/// </summary>
/// <returns>	int型の色コード	</returns>
int color::Color::GetColorCode()
{
	return GetColor(red_,green_,blue_);
}


