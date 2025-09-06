#pragma once
#include"ColliderComp.h"
#include"GameObject.h"
#include"PlayerState.h"
#include"PlayerStateController.h"
#include"input.h"
#include"sword.h"

//	剣で必要な制御や当たり判定をこのクラスで行う
class SwordController : public ColliderComp {

	//	入力判定
	void isInput() {
		auto stateCom = GetGameObj()->GetComponent<StateController>();
		if (!stateCom)return;
		//	入力を行えるかどうかを判定する
		if (!stateCom->CanAttack()) return;
		//	入力判定
		if (Input::IsMouseOn(MOUSE_INPUT_LEFT)) {
			auto sword = GetGameObj()->GetComponent<Sword>();
			if (!sword) return;

	
			//	プレイヤーの向きからどの方向に攻撃を繰り出すかを判定
			//	それに基づいて必要な情報の初期化
			sword->Start();

			//	状態の変更
			stateCom->RequestAttack();
		}
	}

public:

	/// <summary>
	/// プレイヤーの向きと状態に合わせて剣の角度を更新する
	/// </summary>
	void Update()override {

		//	スタート判定
		isInput();

		auto state = GetGameObj()->GetComponent<PlayerStateComp>();
		if (!state) return;

		//	攻撃状態だけ通す
		if (state->GetState() != _P_STATE::Attack) return;
		
		
		
	}


private:

};