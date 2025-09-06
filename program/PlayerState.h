#pragma once
#include"Component.h"
#include"hp.h"
#include"DebugLog.h"


#define _P_STATE  PlayerStateComp::State

/// <summary>
/// プレイヤーの状態だけを管理する。
/// 状態制御などは他のクラスで管理する。
/// </summary>
class PlayerStateComp : public Component
{
public:
	enum class State {
		Idle,	//	待機
		Move,	//	走り
		Jump,	//	ジャンプ
		Attack,	//	攻撃
		swing,	//	スイングワイヤー
		dive,	//	ダイブワイヤー
		damage,	//	ダメージ
		dead,	//	死亡
	}; // enum class

	//	初期化
	PlayerStateComp(const status::HP& hp, State state = State::Idle)
		:hp_(hp),state_(state)
	{
		DebugLog::AddDubug("player state:", static_cast<int>(state_));
	}

	virtual ~PlayerStateComp() = default;


	//	状態設定
	void SetState(State state) { 
		state_ = state; 
	}

	//	状態取得
	State GetState()const { return state_; }

	//	更新処理
	void Update()override {}

	//	体力クラス
	status::HP hp_;

private:
	//	現在の状態
	State state_;

}; // class