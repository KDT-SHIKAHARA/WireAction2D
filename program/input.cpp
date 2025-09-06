#include "input.h"

//	������
InputManager::InputManager(){
	//	�L�[������
	keyStates_.fill(0);
	prevKeyState_.fill(0);
	//	�}�E�X������
	mouseState_ = prevMouseState_ = 0;
	//	pad������
	padState_ = prevPadState_ = 0;

	//	���̓f�o�C�X������
	currentDevice = InputDevice::Keyboard;

}

/// <summary>
/// �S�f�o�C�X�̓��͏�Ԃ��擾���A�ϐ��Ɋi�[
/// </summary>
void InputManager::Update(){
	prevKeyState_ = keyStates_;	//	�O����͏�ԕێ�
	GetHitKeyStateAll(keyStates_.data());	//	�S���͏�Ԏ擾

	prevMouseState_ = mouseState_;	//	�O����͕ێ�
	mouseState_ = GetMouseInput();	//	�S���͎擾

	mouseWheel = GetMouseWheelRotVol();	//	�}�E�X�z�C�[���̓��͎擾
	GetMousePoint(&mouseX_, &mouseY_);	//	�}�E�X���W�擾

	prevPadState_ = padState_;	//	�O����͕ێ�
	if (GetJoypadNum() > 0) padState_ = GetJoypadInputState(DX_INPUT_PAD1);	//	pad���q�����Ă���Ƃ������S�擾

	//	���݂̓��̓f�o�C�X����
	if (padState_ != 0) currentDevice = InputDevice::Gamepad;
	else if (mouseState_ != 0) currentDevice = InputDevice::Mouse;
	else if (anyKey()) currentDevice = InputDevice::Keyboard;
}

/// <summary>
/// �L�[���͔���i�P�����j
/// </summary>
/// <param name="arg_keyID">	�L�[�R�[�h </param>
/// <returns> true: ���ݓ��� > 0 and prevKeyState_ == 0; </returns>	
bool InputManager::IsKeyOn(int arg_keyID)const {
	return keyStates_[arg_keyID] && !prevKeyState_[arg_keyID];
}


/// <summary>
/// �L�[���͔���i�A���j
/// </summary>
/// <param name="arg_keyID">	�L�[�R�[�h </param>
/// <returns> true:	���ݓ��� > 0	</returns>
bool InputManager::IsKeyPressed(int arg_keyID)const{
	return keyStates_[arg_keyID];
}

/// <summary>
/// �}�E�X���͔���i�P�����j
/// </summary>
/// <param name="arg_mouseID">	�}�E�X�R�[�h </param>
/// <returns>	true: mouseState AND  !prevMouseState_  </returns>
bool InputManager::IsMouseOn(int arg_mouseID)const {
	return (mouseState_ & arg_mouseID) && !(prevMouseState_ & arg_mouseID);
}

/// <summary>
/// �}�E�X���͔���i�������j
/// </summary>
/// <param name="arg_mouseID">	�}�E�X�R�[�h </param>
/// <returns>	true: mouseState != 0 </returns>
bool InputManager::IsMousePressed(int arg_mouseID)const {
	return (mouseState_ & arg_mouseID) != 0;
}

/// <summary>
/// PAD���͔���i�P�����j
/// </summary>
/// <param name="arg_padID">	PAD�R�[�h </param>
/// <returns>	true: padState_ AND  !prevPadState_ </returns>
bool InputManager::IsPadOn(int arg_padID) const{
	return (padState_ & arg_padID) && !(prevPadState_ & arg_padID);
}

/// <summary>
/// PAD���͔���i�������j
/// </summary>
/// <param name="arg_padID"> pad�R�[�h</param>
/// <returns> true: padState_ != 0</returns>
bool InputManager::IsPadPressed(int arg_padID) const{
	return (padState_ & arg_padID) != 0;
}


int InputManager::GetMouseWheel()const
{
	return mouseWheel;
}

int InputManager::MouseX() const
{
	return mouseX_;
}

int InputManager::MouseY() const
{
	return mouseY_;
}


/// ���͊Ǘ��̃��\�b�h�擾�p�̃��b�p�[
bool Input::IsKeyOn(int arg_keyID)
{
	return InputManager::Instance().IsKeyOn(arg_keyID);
}
bool Input::IsKeyPressed(int arg_keyID)
{
	return InputManager::Instance().IsKeyPressed(arg_keyID);
}
bool Input::IsMouseOn(int arg_mouseID)
{
	return InputManager::Instance().IsMouseOn(arg_mouseID);
}
bool Input::IsMousePressed(int arg_mouseID)
{
	return InputManager::Instance().IsMousePressed(arg_mouseID);
}
bool Input::IsPadOn(int arg_padID)
{
	return InputManager::Instance().IsPadOn(arg_padID);
}
bool Input::IsPadPressed(int arg_padID)
{
	return InputManager::Instance().IsPadPressed(arg_padID);
}
int Input::GetMouseWheel()
{
	return InputManager::Instance().GetMouseWheel();
}
int Input::MouseX()
{
	return InputManager::Instance().MouseX();
}
int Input::MouseY()
{
	return InputManager::Instance().MouseY();
}
