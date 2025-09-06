#pragma once
#include"GameObject.h"

enum class PlayerState {
	idle,//	�ҋ@
	move,//	�ړ�
	jump,//	�W�����v
	attack,//	�U��
	swing,//	�X�C���O���C���[�@
	dive,//	�_�C�u���C���[
	MAX,//	�ő吔
};

class Player :public GameObject {
	PlayerState state;
public:
	Player();
	virtual ~Player() = default;

	//	�R���|�[�l���g�ǉ�
	void SetComponent();

	//	�X�V�A�`��71
	void Update()override;
	void Render()override;



};