#pragma once
#include"Component.h"
#include"hp.h"
#include"DebugLog.h"


#define _P_STATE  PlayerStateComp::State

/// <summary>
/// �v���C���[�̏�Ԃ������Ǘ�����B
/// ��Ԑ���Ȃǂ͑��̃N���X�ŊǗ�����B
/// </summary>
class PlayerStateComp : public Component
{
public:
	enum class State {
		Idle,	//	�ҋ@
		Move,	//	����
		Jump,	//	�W�����v
		Attack,	//	�U��
		swing,	//	�X�C���O���C���[
		dive,	//	�_�C�u���C���[
		damage,	//	�_���[�W
		dead,	//	���S
	}; // enum class

	//	������
	PlayerStateComp(const status::HP& hp, State state = State::Idle)
		:hp_(hp),state_(state)
	{
		DebugLog::AddDubug("player state:", static_cast<int>(state_));
	}

	virtual ~PlayerStateComp() = default;


	//	��Ԑݒ�
	void SetState(State state) { 
		state_ = state; 
	}

	//	��Ԏ擾
	State GetState()const { return state_; }

	//	�X�V����
	void Update()override {}

	//	�̗̓N���X
	status::HP hp_;

private:
	//	���݂̏��
	State state_;

}; // class