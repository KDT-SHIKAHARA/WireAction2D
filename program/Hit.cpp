#include "Hit.h"

bool Hit::CheckCircleRect(const Vector2D<float>& rect_pos, const Vector2D<float>& rect_size, const Vector2D<float>& circle_pos, float radius)
{

	//	右下座標
	auto right = rect_pos + rect_size;

	//	円の中心に一番近い四角形内の点を求める
	float closestX = std::max(rect_pos.x, std::min(circle_pos.x, right.x));
	float closestY = std::max(rect_pos.y, std::min(circle_pos.y, right.y));


	//	求めた点と円との距離
	float dx = circle_pos.x - closestX;
	float dy = circle_pos.y - closestY;

	return (dx * dx + dy * dy) <= (radius * radius);

}
