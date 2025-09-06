#include "Hit.h"

bool Hit::CheckCircleRect(const Vector2D<float>& rect_pos, const Vector2D<float>& rect_size, const Vector2D<float>& circle_pos, float radius)
{

	//	�E�����W
	auto right = rect_pos + rect_size;

	//	�~�̒��S�Ɉ�ԋ߂��l�p�`���̓_�����߂�
	float closestX = std::max(rect_pos.x, std::min(circle_pos.x, right.x));
	float closestY = std::max(rect_pos.y, std::min(circle_pos.y, right.y));


	//	���߂��_�Ɖ~�Ƃ̋���
	float dx = circle_pos.x - closestX;
	float dy = circle_pos.y - closestY;

	return (dx * dx + dy * dy) <= (radius * radius);

}
