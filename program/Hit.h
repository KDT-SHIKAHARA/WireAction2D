#pragma once
#define NOMINMAX

#include"vector2d.h"
#include<algorithm>
#include<cmath>


class Hit {
public:
	//	円と円の当たり判定
	static bool CheckCircle(const Vector2D<float>& pos_1, float radius_1, const Vector2D<float>& pos_2, float radius_2) {
		return Get2Distance(pos_1, pos_2) <= (radius_1 + radius_2);
	}


	/// <summary>
	///	円と四角形の当たり判定
	/// </summary>
	/// <param name="rect_pos"> 四角形の左上座標 </param>
	/// <param name="rect_size"> 四角形のサイズ </param>
	/// <param name="circle_pos"> 円の中心座標 </param>
	/// <param name="radius"> 円の半径 </param>
	/// <returns> true: 衝突 false: 未衝突 </returns>
	static bool CheckCircleRect(const Vector2D<float>& rect_pos, const Vector2D<float>& rect_size,
		const Vector2D<float>& circle_pos, float radius);


	// 点と四角形の当たり判定
	static bool CheckPointRect(const Vector2D<float>& point,
		const Vector2D<float>& rectPos,
		const Vector2D<float>& rectSize)
	{
		return (point.x >= rectPos.x) &&
			(point.x <= rectPos.x + rectSize.x) &&
			(point.y >= rectPos.y) &&
			(point.y <= rectPos.y + rectSize.y);
	}


};