#include "JumpComp.h"
#include "RigidbodyComp.h"
#include "input.h"
#include "PlayerStateController.h"
#include"GameObject.h"


void JumpComp::Update(){

	//	���s�ɕK�v�ȃR���|�[�l���g�����݂��Ă��邩
	auto state = GetGameObj()->GetComponent<StateController>();

	//	�������Z
	auto rigid = GetGameObj()->GetComponent<RigidbodyComp>();

	if (!state || !rigid) return;
	if (!state->CanJump()) return;

	//	�W�����v����
	if (state->isSpace) return;

	if (Input::IsKeyOn(KEY_INPUT_SPACE)) {
		rigid->SetVelocity({ rigid->velocity().x,jump_velocity_});
		state->RequestJump();
	}
}
