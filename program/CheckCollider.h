#pragma once
#include "vector2d.h"
#include "CircleCollider.h"

class CheckCollider {
	CheckCollider() = default;
	virtual ~CheckCollider() = default;
public:
	CheckCollider(const CheckCollider&) = delete;
	CheckCollider& operator=(const CheckCollider&) = delete;

	static CheckCollider& Instance() {
		static CheckCollider instance;
		return instance;
	}


	template<typename T>
	float GetDistance(const Vector2D<T>& arg_first, const Vector2D<T>& arg_second) {
		Value<float> tmp_vec = arg_first - arg_second;
		float distance = sqrtf(tmp_vec.x * tmp_vec.x + tmp_vec.y * tmp_vec.y);
		return distance;
	}

	bool CheckCircleCollision(const Circle2D& arg_first, const Circle2D& arg_second) {
		float distance = GetDistance(arg_first.position(), arg_second.position());
		float radius = arg_first.radius() + arg_second.radius();
		return  distance <= radius;
	}
};