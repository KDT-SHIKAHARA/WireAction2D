#pragma once
#include"Component.h"
#include"vector2d.h"
#include"flag.h"

/// <summary>
/// �����蔻��ɕK�v�ȏ����擾����
/// </summary>
class ColliderComp : public Component{
	Vector2D<float> size_;
public:
	ColliderComp(Vector2D<float> arg_size = { 10,10 })
		:size_(arg_size){ }

	Vector2D<float> size() const { return size_; }
	void Update()override{}

	Flag isActive = true;
	Flag isPush = true;
};
