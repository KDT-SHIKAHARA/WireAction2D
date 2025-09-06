#include "JumpComp.h"
#include "RigidbodyComp.h"
#include "input.h"
#include "PlayerStateController.h"
#include"GameObject.h"


void JumpComp::Update(){

	//	実行に必要なコンポーネントが存在しているか
	auto state = GetGameObj()->GetComponent<StateController>();

	//	物理演算
	auto rigid = GetGameObj()->GetComponent<RigidbodyComp>();

	if (!state || !rigid) return;
	if (!state->CanJump()) return;

	//	ジャンプ入力
	if (state->isSpace) return;

	if (Input::IsKeyOn(KEY_INPUT_SPACE)) {
		rigid->SetVelocity({ rigid->velocity().x,jump_velocity_});
		state->RequestJump();
	}
}
