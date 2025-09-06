#pragma once
#include <string>
#include "input.h"
#include "vector2d.h"
#include "Hit.h"
#include "dxlib.h"
#include "GetColor.h"

class BoxButton {
	Vector2Df position_;	//	座標
	Vector2Df size_;		//	サイズ
	std::string str_;		//	文字列
public:

	BoxButton(const Vector2Df& pos, const Vector2Df& size,const std::string& str) {
		size_ = size;
		position_ = pos - size / 2.f;
		str_ = str;
	}

	//	マウス座標との当たり判定
	bool ChecKMouseHit() {
		Vector2Df mouse{ (float)Input::MouseX(),(float)Input::MouseY() };
			return Hit::CheckPointRect(mouse, position_, size_);
	}

	void Draw(unsigned int color) {
		int textWidth = GetDrawStringWidth(str_.c_str(), str_.size());
		int textHeight = GetFontSize();

		float drawX = position_.x + size_.x / 2.0f - textWidth / 2.0f;
		float drawY = position_.y + size_.y / 2.0f - textHeight / 2.0f;

		DrawString(static_cast<int>(drawX), static_cast<int>(drawY), str_.c_str(), color);

//#ifdef _DEBUG
//		DrawBoxAA(position_.x, position_.y, position_.x + size_.x, position_.y + size_.y, RED, FALSE);
//#endif // _DEBUG

	}

	Vector2Df Position()const { return position_; }
	Vector2Df Size()const { return size_; }


};