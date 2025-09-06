#pragma once
#include "Collider.h"
#include "vector2d.h"

class Circle2D :public Collider {
protected:
	Vector2D<float> position_;
	float radius_;
public:
	Circle2D(const Vector2D<float>& arg_position,const float& arg_radius, const ObjectType& arg_objectType_)
		: Collider(arg_objectType_),position_(arg_position), radius_(arg_radius){ }
	virtual ~Circle2D() = default;

	virtual void OnCollision(int arg_power)override = 0;

	Vector2D<float> position()const { return position_; }
	float radius()const { return radius_; }
};