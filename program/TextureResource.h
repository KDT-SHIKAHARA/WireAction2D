#pragma once

/// <summary>
/// �摜�ǊǗ��N���X
/// �����N���X�Ő��������āA�Q�[���}�l�[�W���[�ŊǗ�������B
/// 1�x�ǂݍ��񂾉摜���\�[�X���g���܂킷
/// </summary>
class TextureResource {
private:
	//	�摜�n���h��
	int handle = -1;

public:
	//	�摜�n���h���̐ݒ�
	TextureResource(int arg_handle) {
		this->handle = arg_handle;

	}

	//	�摜�n���h���̎擾
	int GetHandle()const {

		return handle;
	}
};
