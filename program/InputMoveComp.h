#pragma once
#include"Component.h"
#include"flag.h"



class InputMove :public Component {
public:
	virtual ~InputMove() = default;
	void Update()override;

	//	true: ���͉\ false: ���͕s��
	Flag isInput = true;

	//	���]�t���O
	Flag isReverse = false;

private:


	//	1�b�Ԃ̈ړ����x
	const float move_speed_ = 50.0f;
};