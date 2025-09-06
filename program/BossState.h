#pragma once
#include"Component.h"



enum class BossState {
	Idle,
	Move,
	Laser,
	PhotonRay,

};	//	enum class

/// <summary>
/// �{�X�̏�ԊǗ�������
/// </summary>
class BossStateComp : public Component {

public:
	void SetState(BossState state) { state_ = state; }
	BossState GetState()const { return state_; }
	void Update()override{}

private:
	BossState state_ = BossState::Idle;

}; // class
