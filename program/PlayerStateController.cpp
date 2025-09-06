#include "PlayerStateController.h"
#include"GameObject.h"
#include"RigidbodyComp.h"
#include"InputMoveComp.h"
#include"DebugLog.h"
#include "dive wire.h"
#include "sword.h"
#include "SwingWire.h"

/// <summary>
/// state�R���|�[�l���g�̎擾
/// </summary>
void StateController::Start()
{
	state_ = GetGameObj()->GetComponent<PlayerStateComp>();

}


/// <summary>
/// �e�R���|�[�l���g�̏I����Ԃ��I�����胁�\�b�h�����ď�Ԃ̏I�����Ǘ�����
/// </summary>
void StateController::Update() {
	const auto& Rigid = GetGameObj()->GetComponent<RigidbodyComp>();
	if (!state_ || !Rigid)return;
	auto state = state_->GetState();
	//	��Ԃ̏I������
	//	�I��������ҋ@��Ԃɖ߂�
	switch (state) {
	case _P_STATE::Idle:
		break;

	case _P_STATE::Move: {
		const auto& vector = GetGameObj()->GetComponent<RigidbodyComp>()->velocity();

		//	�ړ��ʂ��Ȃ�������ҋ@��Ԃɂ���
		if (vector.x == 0.0f) {
			state_->SetState(_P_STATE::Idle);
		}
		break;
	}

	case _P_STATE::Jump: {
		//	���n���Ă�����ҋ@��Ԃɂ���
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
