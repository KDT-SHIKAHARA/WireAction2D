#pragma once
#include "Component.h"
#include "BossState.h"
#include "GameObject.h"


/// <summary>
/// 状態移行の管理
/// </summary>
class BossStateController : public Component {

public:
	void Start() { state_ = GetGameObj()->GetComponent<BossStateComp>(); }
	//	状態の終了条件を判定して、状態の切り替え
	void Update()override;

	//	状態変更リクエスト

	void RequestLaser() {
		if (!state_)return;
		if(!CanMove())return;
		state_->SetState(BossState::Laser);
	}


	//	状態変更可能判定
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