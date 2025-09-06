#pragma once
#include <algorithm>
#include <cassert>
#include "Component.h"
#include "flag.h"
#include "Time.h"

class Health : public Component {
protected:
	//	上限下限
	void clamp() { current_ = std::clamp(current_, 0, max_); }

public:
	
	//	初期化
	Health(int max = 10,double invi_max = 1.0) : max_(max), current_(max) {
		assert(max > 0);
		if (invi_max < 0) invi_max = 0;
		invi_max_ = invi_max;
		alive_ = true;
	}


	//	回復
	void Heal(int amount) {
		if (!alive_)return;
		if (amount < 0) amount = 0;
		current_ += amount;
		clamp();
	}

	//	ダメージ
	void Damage(int amount) {
		if (!alive_)return;
		if (amount < 0) amount = 0;
		current_ -= amount;
		clamp();
	}

	//	体力のパーセント表示
	float Percent() const {
		return current_ / max_;
	}

	//	最大体力更新
	void SetMax_(int max) {
		max_ = max;
	}

	//	アクセサ
	int Current()const { return current_; }
	int Max()const { return max_; }


	/// <summary>
	///	無敵時間の経過と判定
	/// </summary>
	void Update()override {
		//	無敵時間の経過判定
		if (invi_time_ < invi_max_)
			invi_time_ += Time::deltaTime();

		//	生存判定
		if (current_ <= 0)
			alive_.Set(false);
	}

protected:
	double invi_time_ = 0;	//	無敵時間
	double invi_max_;		//	無敵時間の最大時間
	int current_;			//	今の体力
	int max_;				//	最大の体力
public:
	Flag alive_;			//	生存判定
	Flag invincible_;		//	無敵判定

};