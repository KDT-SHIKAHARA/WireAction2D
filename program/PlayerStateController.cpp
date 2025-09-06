#include "PlayerStateController.h"
#include"GameObject.h"
#include"RigidbodyComp.h"
#include"InputMoveComp.h"
#include"DebugLog.h"
#include "dive wire.h"
#include "sword.h"
#include "SwingWire.h"

/// <summary>
/// stateコンポーネントの取得
/// </summary>
void StateController::Start()
{
	state_ = GetGameObj()->GetComponent<PlayerStateComp>();

}


/// <summary>
/// 各コンポーネントの終了状態を終了判定メソッドを見て状態の終了を管理する
/// </summary>
void StateController::Update() {
	const auto& Rigid = GetGameObj()->GetComponent<RigidbodyComp>();
	if (!state_ || !Rigid)return;
	auto state = state_->GetState();
	//	状態の終了判定
	//	終了したら待機状態に戻す
	switch (state) {
	case _P_STATE::Idle:
		break;

	case _P_STATE::Move: {
		const auto& vector = GetGameObj()->GetComponent<RigidbodyComp>()->velocity();

		//	移動量がなかったら待機状態にする
		if (vector.x == 0.0f) {
			state_->SetState(_P_STATE::Idle);
		}
		break;
	}

	case _P_STATE::Jump: {
		//	着地していたら待機状態にする
		if (Rigid->isGrounded_ && Rigid->velocity().y <= 0.0f) {
			state_->SetState(_P_STATE::Idle);
		}
		break;

	}

	case _P_STATE::dive:
	{
		const auto& dive_wire = GetGameObj()->GetComponent<DiveWire>();
		if (!dive_wire)return;
		if (dive_wire->IsFinished()) {
			state_->SetState(_P_STATE::Idle);
			Rigid->isStatic_.Set(false);
			dive_wire->ReSet();
		}
	}
		break;

	case _P_STATE::swing:
	{
		auto swingWire = GetGameObj()->GetComponent<SwingWire>();
		if (!swingWire) return;
		if (swingWire->IsFinish()) {
			state_->SetState(_P_STATE::Idle);
			Rigid->isStatic_.Set(false);
			swingWire->Release();
		}

	}
		break;

	case _P_STATE::Attack:
	{
		const auto& sword = GetGameObj()->GetComponent<Sword>();
		if (!sword) return;
		if (sword->isFinish()) {
			state_->SetState(_P_STATE::Idle);
		}

	}
		break;
	}

}
