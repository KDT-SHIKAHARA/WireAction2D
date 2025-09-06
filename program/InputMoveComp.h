#pragma once
#include"Component.h"
#include"flag.h"



class InputMove :public Component {
public:
	virtual ~InputMove() = default;
	void Update()override;

	//	true: 入力可能 false: 入力不可
	Flag isInput = true;

	//	反転フラグ
	Flag isReverse = false;

private:


	//	1秒間の移動速度
	const float move_speed_ = 50.0f;
};