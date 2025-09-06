#pragma once
#include<array>
#include"DxLib.h"


//	入力種別
enum class InputDevice {
	Keyboard,
	Gamepad,
	Mouse,
};

/// <summary>
/// マウス、キーボード、PADの入力状態を取得して、管理する
/// </summary>
class InputManager {
	//	初期化
	InputManager();
	virtual ~InputManager() = default;

	//	キー入力の判定
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

	//	入力状態全体更新
	void Update();

	//	キー入力
	bool IsKeyOn(int arg_keyID)const;	//	単押し
	bool IsKeyPressed(int arg_keyID)const;	//	連続

	//	マウス入力判定
	bool IsMouseOn(int arg_mouseID)const;	//	単押し
	bool IsMousePressed(int arg_mouseID)const;	//	連続

	//	pad入力判定
	bool IsPadOn(int arg_padID)const;	//	単押し
	bool IsPadPressed(int arg_padID)const;	//	長押し

	//	マウスホイール回転量
	int GetMouseWheel()const;

	//	マウス座標
	int MouseX()const;
	int MouseY()const;
private:
	InputDevice currentDevice = InputDevice::Keyboard;	//	現在の入力デバイス
	int mouseState_ = 0, prevMouseState_ = 0;	//	マウス入力状態用
	int padState_ = 0, prevPadState_ = 0;	//	pad入力状態用
	int mouseX_, mouseY_ = 0;	//	マウス座標
	int mouseWheel = 0;	//	マウスホイールの回転量
	std::array<char, 256> keyStates_, prevKeyState_;	//	キー入力状態用

};


/// <summary>
/// 入力管理のメソッド取得用のラッパー
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