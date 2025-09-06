#pragma once
#define NOMINMAX

#include"vector2d.h"
#include<algorithm>
#include<cmath>


class Hit {
public:
	//	�~�Ɖ~�̓����蔻��
	static bool CheckCircle(const Vector2D<float>& pos_1, float radius_1, const Vector2D<float>& pos_2, float radius_2) {
		return Get2Distance(pos_1, pos_2) <= (radius_1 + radius_2);
	}


	/// <summary>
	///	�~�Ǝl�p�`�̓����蔻��
	/// </summary>
	/// <param name="rect_pos"> �l�p�`�̍�����W </param>
	/// <param name="rect_size"> �l�p�`�̃T�C�Y </param>
	/// <param name="circle_pos"> �~�̒��S���W </param>
	/// <param name="radius"> �~�̔��a </param>
	/// <returns> true: �Փ� false: ���Փ� </returns>
	static bool CheckCircleRect(const Vector2D<float>& rect_pos, const Vector2D<float>& rect_size,
		const Vector2D<float>& circle_pos, float radius);


	// �_�Ǝl�p�`�̓����蔻��
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