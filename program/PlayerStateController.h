#pragma once
#include"PlayerState.h"
#include"Component.h"


/// <summary>
/// �v���C���[�̏�Ԃ𐧌䂷��B
/// �e�R���|�[�l���g�̏I�����\�b�h�����Ԃ̕ύX���s��
/// �����ł͏�Ԃ̕ω��������s���āA��ԕω������ď������s�����ǂ�����
/// �e�R���|�[�l���g�Ŋm�F����
/// </summary>
class StateController : public Component {
public:
	void Start();
	void Update()override;

	// ��ԕύX���N�G�X�g
	//	�W�����v
	void RequestJump() {
		if (!state_) return;
		//	�ҋ@�A�ړ�
		if (CanJump()) {
			state_->SetState(_P_STATE::Jump);
		}
	}

	//	�ړ�
	void RequestMove() {
		if (!state_) return;
		//	�ҋ@�A�ړ��A�W�����v
		if (CanMove()) {
			//	�W�����v��Ԃ���Ȃ����
			if (state_->GetState() != _P_STATE::Jump)
				//	�ړ���Ԃɂ���
				state_->SetState(_P_STATE::Move);
			state_;
		}

	}

	//	�_�C�u���C���[
	void RequestDiveWire() {
		if (!state_) return;
		if (CanDiveWire()) {
			//	��Ԃ̕ύX
			state_->SetState(_P_STATE::dive);
		}
	}

	//	�_�C�u���C���[
	void RequestSwingWire() {
		if (!state_) return;
		if (CanSwingWire()) {
			//	��Ԃ̕ύX
			state_->SetState(_P_STATE::swing);
		}
	}

	//	�U��
	void RequestAttack() {
		if (!state_) return;
		if (CanAttack()) {
			//	��Ԃ̕ύX
			state_->SetState(_P_STATE::Attack);
		}
	}


	//	��ԕύX�\����
	//	�W�����v
	bool CanJump()const {
		auto state = state_->GetState();
		return state == _P_STATE::Idle || state == _P_STATE::Move;
	}

	//	�ړ�
	bool CanMove()const {
		auto state = state_->GetState();
		return	
			state == _P_STATE::Idle ||
			state == _P_STATE::Move ||
			state == _P_STATE::Jump;
	}

	bool CanInput()const {
		auto state = state_->GetState();
		return 
			state == _P_STATE::Idle ||
			state == _P_STATE::Move ||
			state == _P_STATE::Jump || 
			state == _P_STATE::Attack;

	}

	//	�_�C�u���C���[
	bool CanDiveWire()const {
		auto state = state_->GetState();
		return
			state == _P_STATE::Idle ||
			state == _P_STATE::Move ||
			state == _P_STATE::Jump;

	}

	bool CanSwingWire()const {
		auto state = state_->GetState();
		return
			state == _P_STATE::Idle ||
			state == _P_STATE::Move ||
			state == _P_STATE::Jump;
	}

	//	�U��
	bool CanAttack()const {
		auto state = state_->GetState();
		return
			state == _P_STATE::Idle ||
			state == _P_STATE::Move ||
			state == _P_STATE::Jump;
	}


	Flag isSpace = false;
private:
	std::shared_ptr<PlayerStateComp> state_;

};