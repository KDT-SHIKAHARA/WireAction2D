#pragma once
#include "Component.h"
#include "BossState.h"
#include "GameObject.h"


/// <summary>
/// ��Ԉڍs�̊Ǘ�
/// </summary>
class BossStateController : public Component {

public:
	void Start() { state_ = GetGameObj()->GetComponent<BossStateComp>(); }
	//	��Ԃ̏I�������𔻒肵�āA��Ԃ̐؂�ւ�
	void Update()override;

	//	��ԕύX���N�G�X�g

	void RequestLaser() {
		if (!state_)return;
		if(!CanMove())return;
		state_->SetState(BossState::Laser);
	}


	//	��ԕύX�\����
	bool CanMove() {
		if (!state_)return false;
		auto state = state_->GetState();
		return  state == BossState::Idle;
	}


	bool CanPhotonRay() {
		if (!state_)return false;
		auto state = state_->GetState();
		return  state == BossState::Idle;

	}


	bool CanLaser() {
		if (!state_)return false;
		auto state = state_->GetState();
		return state == BossState::Idle;
	}

private:
	std::shared_ptr<BossStateComp> state_;

};