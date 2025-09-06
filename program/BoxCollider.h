#pragma once
#include"Collider.h"
#include "vector2d.h"

/// <summary>
/// ç¿ïWäÓèÄÇÕç∂è„
/// </summary>
class Box2D :public Collider{
protected:
	Vector2D<float> position_;
	Vector2D<int> size_;
public:
	Box2D(const Vector2D<float>& arg_position, const Vector2D<int>& arg_size, const ObjectType& arg_objectType_)
		:Collider(arg_objectType_), position_(arg_position), size_(arg_size){ }
	virtual ~Box2D() = default;

	virtual void OnCollision(int arg_power) = 0;
	Vector2D<float> position()const { return position_; }
	Vector2D<int> size()const { return size_; }

};