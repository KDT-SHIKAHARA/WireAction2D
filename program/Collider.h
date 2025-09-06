#pragma once
#include"ObjectType.h"

class Collider {
protected:
	ObjectType objectType_;
public:
	Collider(const ObjectType& arg_objectType_):objectType_(arg_objectType_){}
	virtual  ~Collider() = default;

	ObjectType objectType() { return objectType_; }
	virtual void OnCollision(int arg_power) = 0;
};
