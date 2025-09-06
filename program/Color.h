#pragma once

#define _COLOR color::

namespace color {

	/// <summary>
	/// 色のブレンド機能を持って自身で自分の色を補完する。
	/// 外部に色を渡すためのメソッドを用意して、コードが欲しいときはカラーコード取得の
	/// メソッドで取得する。
	/// </summary>
	class Color {
		//	色
		int red_;
		int green_;
		int blue_;
	public:
		//	初期化
		Color (const int& arg_red = 0, const int& arg_green = 0,const int& arg_blue = 0)
			:red_(arg_red),green_(arg_green),blue_(arg_blue){ }

		//	補間率で色のブレンド
		void BlendColor(const Color& arg_color1, const Color& arg_color2, const float& arg_colorLerp);

		//	カラーコード取得
		int GetColorCode();

	};

}