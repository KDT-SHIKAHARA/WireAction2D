#pragma once
#include"ColliderComp.h"
#include"GameObject.h"
#include"PlayerState.h"
#include"PlayerStateController.h"
#include"input.h"
#include"sword.h"

//	���ŕK�v�Ȑ���ⓖ���蔻������̃N���X�ōs��
class SwordController : public ColliderComp {

	//	���͔���
	void isInput() {
		auto stateCom = GetGameObj()->GetComponent<StateController>();
		if (!stateCom)return;
		//	���͂��s���邩�ǂ����𔻒肷��
		if (!stateCom->CanAttack()) return;
		//	���͔���
		if (Input::IsMouseOn(MOUSE_INPUT_LEFT)) {
			auto sword = GetGameObj()->GetComponent<Sword>();
			if (!sword) return;

	
			//	�v���C���[�̌�������ǂ̕����ɍU�����J��o�����𔻒�
			//	����Ɋ�Â��ĕK�v�ȏ��̏�����
			sword->Start();

			//	��Ԃ̕ύX
			stateCom->RequestAttack();
		}
	}

public:

	/// <summary>
	/// �v���C���[�̌����Ə�Ԃɍ��킹�Č��̊p�x���X�V����
	/// </summary>
	void Update()override {

		//	�X�^�[�g����
		isInput();

		auto state = GetGameObj()->GetComponent<PlayerStateComp>();
		if (!state) return;

		//	�U����Ԃ����ʂ�
		if (state->GetState() != _P_STATE::Attack) return;
		
		
		
	}


private:

};