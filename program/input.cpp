#include "input.h"

//	初期化
InputManager::InputManager(){
	//	キー初期化
	keyStates_.fill(0);
	prevKeyState_.fill(0);
	//	マウス初期化
	mouseState_ = prevMouseState_ = 0;
	//	pad初期化
	padState_ = prevPadState_ = 0;

	//	入力デバイス初期化
	currentDevice = InputDevice::Keyboard;

}

/// <summary>
/// 全デバイスの入力状態を取得し、変数に格納
/// </summary>
void InputManager::Update(){
	prevKeyState_ = keyStates_;	//	前回入力状態保持
	GetHitKeyStateAll(keyStates_.data());	//	全入力状態取得

	prevMouseState_ = mouseState_;	//	前回入力保持
	mouseState_ = GetMouseInput();	//	全入力取得

	mouseWheel = GetMouseWheelRotVol();	//	マウスホイールの入力取得
	GetMousePoint(&mouseX_, &mouseY_);	//	マウス座標取得

	prevPadState_ = padState_;	//	前回入力保持
	if (GetJoypadNum() > 0) padState_ = GetJoypadInputState(DX_INPUT_PAD1);	//	padが繋がっているときだけ全取得

	//	現在の入力デバイス判定
	if (padState_ != 0) currentDevice = InputDevice::Gamepad;
	else if (mouseState_ != 0) currentDevice = InputDevice::Mouse;
	else if (anyKey()) currentDevice = InputDevice::Keyboard;
}

/// <summary>
/// キー入力判定（単押し）
/// </summary>
/// <param name="arg_keyID">	キーコード </param>
/// <returns> true: 現在入力 > 0 and prevKeyState_ == 0; </returns>	
bool InputManager::IsKeyOn(int arg_keyID)const {
	return keyStates_[arg_keyID] && !prevKeyState_[arg_keyID];
}


/// <summary>
/// キー入力判定（連続可）
/// </summary>
/// <param name="arg_keyID">	キーコード </param>
/// <returns> true:	現在入力 > 0	</returns>
bool InputManager::IsKeyPressed(int arg_keyID)const{
	return keyStates_[arg_keyID];
}

/// <summary>
/// マウス入力判定（単押し）
/// </summary>
/// <param name="arg_mouseID">	マウスコード </param>
/// <returns>	true: mouseState AND  !prevMouseState_  </returns>
bool InputManager::IsMouseOn(int arg_mouseID)const {
	return (mouseState_ & arg_mouseID) && !(prevMouseState_ & arg_mouseID);
}

/// <summary>
/// マウス入力判定（長押し可）
/// </summary>
/// <param name="arg_mouseID">	マウスコード </param>
/// <returns>	true: mouseState != 0 </returns>
bool InputManager::IsMousePressed(int arg_mouseID)const {
	return (mouseState_ & arg_mouseID) != 0;
}

/// <summary>
/// PAD入力判定（単押し）
/// </summary>
/// <param name="arg_padID">	PADコード </param>
/// <returns>	true: padState_ AND  !prevPadState_ </returns>
bool InputManager::IsPadOn(int arg_padID) const{
	return (padState_ & arg_padID) && !(prevPadState_ & arg_padID);
}

/// <summary>
/// PAD入力判定（長押し）
/// </summary>
/// <param name="arg_padID"> padコード</param>
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


/// 入力管理のメソッド取得用のラッパー
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
