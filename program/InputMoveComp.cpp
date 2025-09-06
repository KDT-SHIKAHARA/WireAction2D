#include "InputMoveComp.h"
#include"GameObject.h"
#include"input.h"
#include"RigidbodyComp.h"
#include"PlayerStateController.h"
#include"Time.h"
/// <summary>
/// 入力状態を参照して、入力移動量を設定する。
/// </summary>
void InputMove::Update(){
	//	入力を行うかどうかの判定
	if (!isInput) return;

	//	実行可能状態
	auto state = GetGameObj()->GetComponent<StateController>();

	//	入力に応じた移動量を設定する
	auto rigid_ptr = GetGameObj()->GetComponent<RigidbodyComp>();

	//	必要なコンポーネントがついているか確認
	if (!rigid_ptr || !state) return;

	//	実行不可なら処理を終了
	if (!state->CanInput()) return;

	////	上
	//if (Input::IsKeyPressed(KEY_INPUT_W)) {
	//	if (!rigid_ptr->isGrounded_)return;
	//	GetGameObj()->transform.SetRotation(90.0f * DegToRad);
	//}


	////	下
	//if (Input::IsKeyPressed(KEY_INPUT_W)) {
	//	//	着地していたら下方向にしない
	//	if (rigid_ptr->isGrounded_)return;
	//	GetGameObj()->transform.SetRotation(270.0f * DegToRad);
	//}

	//	左
	float speed = move_speed_;
	if (!rigid_ptr->isGrounded_) {
		speed *= 0.3f;
	}


		if (Input::IsKeyPressed(KEY_INPUT_A)) {
			rigid_ptr->AddVelocity({ -speed  ,0 });
			GetGameObj()->transform.SetRotation(180.0f * DegToRad);
			isReverse = true;
			state->RequestMove();
		}

		//	右
		if (Input::IsKeyPressed(KEY_INPUT_D)) {
			rigid_ptr->AddVelocity({ speed  ,0 });
			GetGameObj()->transform.SetRotation(0.0f);
			isReverse = false;
			state->RequestMove();
		}


		// 地上で入力なし → すぐ止める
		if (rigid_ptr->isGrounded_) {
			bool noInput = !Input::IsKeyPressed(KEY_INPUT_A) && !Input::IsKeyPressed(KEY_INPUT_D);
			if (noInput) {
				rigid_ptr->SetVelocity({ 0.0f, rigid_ptr->velocity().y });
			}
		}

}
