#pragma once
#include"GameObject.h"
#include<string>

class Goal {
	inline static std::string posFile = "res/goal/pos";
	inline static std::string texture = "res/goal/texture.png";
public:
	static std::shared_ptr<GameObject> Create(int num);
};

//	�S�[���̃G���e�B�e�B�쐬

//	�v���C���[�^�O�ƏՓ˂����甽���͂�����Scene���ɏՓ˃t���O��n��

//	���C���[�ԍ��́A�P�Œ��ԃ��C���[��