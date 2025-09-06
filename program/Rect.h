#pragma once
#include"Circle.h"

struct Rect {
	float x, y, w, h = 0;

	bool IsCollision(const Rect& other) {
		return !(x + w <= other.x || other.x + other.w <= x ||
			y + h <= other.y || other.y + other.h <= y);
	}

    //  四角形と円の当たり判定
	bool IsCollisionCircle(const Circle& circle)const {
        // 矩形の中心座標
        float centerX = x + w * 0.5f;
        float centerY = y + h * 0.5f;

        // 円の中心と矩形中心の距離の絶対値（X,Y）
        float distX = std::abs(circle.x - centerX);
        float distY = std::abs(circle.y - centerY);

        // 円の中心が矩形の範囲外すぐなら衝突なし
        if (distX > (w * 0.5f + circle.radius)) return false;
        if (distY > (h * 0.5f + circle.radius)) return false;

        // 円の中心が矩形の幅または高さの範囲内なら衝突あり
        if (distX <= (w * 0.5f)) return true;
        if (distY <= (h * 0.5f)) return true;

        // 円の中心から矩形の角までの距離の2乗を計算
        float cornerDistSq = (distX - w * 0.5f) * (distX - w * 0.5f) +
            (distY - h * 0.5f) * (distY - h * 0.5f);

        // 角との距離が半径以内なら衝突あり
        return cornerDistSq <= (circle.radius * circle.radius);
	}
};