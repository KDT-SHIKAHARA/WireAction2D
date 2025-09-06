#pragma once
#include<array>
#include"DxLib.h"


//	���͎��
enum class InputDevice {
	Keyboard,
	Gamepad,
	Mouse,
};

/// <summary>
/// �}�E�X�A�L�[�{�[�h�APAD�̓��͏�Ԃ��擾���āA�Ǘ�����
/// </summary>
class InputManager {
	//	������
	InputManager();
	virtual ~InputManager() = default;

	//	�L�[���͂̔���
	bool anyKey()const {
		for (auto key : keyStates_) {
			if (key) return true;
		}
		return false;
	}

public:
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	
	static InputManager& Instance() {
		static InputManager instance;
		return instance;
	}

	//	���͏�ԑS�̍X�V
	void Update();

	//	�L�[����
	bool IsKeyOn(int arg_keyID)const;	//	�P����
	bool IsKeyPressed(int arg_keyID)const;	//	�A��

	//	�}�E�X���͔���
	bool IsMouseOn(int arg_mouseID)const;	//	�P����
	bool IsMousePressed(int arg_mouseID)const;	//	�A��

	//	pad���͔���
	bool IsPadOn(int arg_padID)const;	//	�P����
	bool IsPadPressed(int arg_padID)const;	//	������

	//	�}�E�X�z�C�[����]��
	int GetMouseWheel()const;

	//	�}�E�X���W
	int MouseX()const;
	int MouseY()const;
private:
	InputDevice currentDevice = InputDevice::Keyboard;	//	���݂̓��̓f�o�C�X
	int mouseState_ = 0, prevMouseState_ = 0;	//	�}�E�X���͏�ԗp
	int padState_ = 0, prevPadState_ = 0;	//	pad���͏�ԗp
	int mouseX_, mouseY_ = 0;	//	�}�E�X���W
	int mouseWheel = 0;	//	�}�E�X�z�C�[���̉�]��
	std::array<char, 256> keyStates_, prevKeyState_;	//	�L�[���͏�ԗp

};


/// <summary>
/// ���͊Ǘ��̃��\�b�h�擾�p�̃��b�p�[
/// </summary>
class Input {
public:
	static bool IsKeyOn(int arg_keyID);
	static bool IsKeyPressed(int arg_keyID);
	static bool IsMouseOn(int arg_mouseID);
	static bool IsMousePressed(int arg_mouseID);
	static bool IsPadOn(int arg_padID);
	static bool IsPadPressed(int arg_padID);
	static int GetMouseWheel();
	static int MouseX();
	static int MouseY();
};