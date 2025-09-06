#pragma once
#include <algorithm>
#include <cassert>
#include "Component.h"
#include "flag.h"
#include "Time.h"

class Health : public Component {
protected:
	//	�������
	void clamp() { current_ = std::clamp(current_, 0, max_); }

public:
	
	//	������
	Health(int max = 10,double invi_max = 1.0) : max_(max), current_(max) {
		assert(max > 0);
		if (invi_max < 0) invi_max = 0;
		invi_max_ = invi_max;
		alive_ = true;
	}


	//	��
	void Heal(int amount) {
		if (!alive_)return;
		if (amount < 0) amount = 0;
		current_ += amount;
		clamp();
	}

	//	�_���[�W
	void Damage(int amount) {
		if (!alive_)return;
		if (amount < 0) amount = 0;
		current_ -= amount;
		clamp();
	}

	//	�̗͂̃p�[�Z���g�\��
	float Percent() const {
		return current_ / max_;
	}

	//	�ő�̗͍X�V
	void SetMax_(int max) {
		max_ = max;
	}

	//	�A�N�Z�T
	int Current()const { return current_; }
	int Max()const { return max_; }


	/// <summary>
	///	���G���Ԃ̌o�߂Ɣ���
	/// </summary>
	void Update()override {
		//	���G���Ԃ̌o�ߔ���
		if (invi_time_ < invi_max_)
			invi_time_ += Time::deltaTime();

		//	��������
		if (current_ <= 0)
			alive_.Set(false);
	}

protected:
	double invi_time_ = 0;	//	���G����
	double invi_max_;		//	���G���Ԃ̍ő厞��
	int current_;			//	���̗̑�
	int max_;				//	�ő�̗̑�
public:
	Flag alive_;			//	��������
	Flag invincible_;		//	���G����

};