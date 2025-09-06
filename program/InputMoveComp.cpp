#include "InputMoveComp.h"
#include"GameObject.h"
#include"input.h"
#include"RigidbodyComp.h"
#include"PlayerStateController.h"
#include"Time.h"
/// <summary>
/// ���͏�Ԃ��Q�Ƃ��āA���͈ړ��ʂ�ݒ肷��B
/// </summary>
void InputMove::Update(){
	//	���͂��s�����ǂ����̔���
	if (!isInput) return;

	//	���s�\���
	auto state = GetGameObj()->GetComponent<StateController>();

	//	���͂ɉ������ړ��ʂ�ݒ肷��
	auto rigid_ptr = GetGameObj()->GetComponent<RigidbodyComp>();

	//	�K�v�ȃR���|�[�l���g�����Ă��邩�m�F
	if (!rigid_ptr || !state) return;

	//	���s�s�Ȃ珈�����I��
	if (!state->CanInput()) return;

	////	��
	//if (Input::IsKeyPressed(KEY_INPUT_W)) {
	//	if (!rigid_ptr->isGrounded_)return;
	//	GetGameObj()->transform.SetRotation(90.0f * DegToRad);
	//}


	////	��
	//if (Input::IsKeyPressed(KEY_INPUT_W)) {
	//	//	���n���Ă����牺�����ɂ��Ȃ�
	//	if (rigid_ptr->isGrounded_)return;
	//	GetGameObj()->transform.SetRotation(270.0f * DegToRad);
	//}

	//	��
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

		//	�E
		if (Input::IsKeyPressed(KEY_INPUT_D)) {
			rigid_ptr->AddVelocity({ speed  ,0 });
			GetGameObj()->transform.SetRotation(0.0f);
			isReverse = false;
			state->RequestMove();
		}


		// �n��œ��͂Ȃ� �� �����~�߂�
		if (rigid_ptr->isGrounded_) {
			bool noInput = !Input::IsKeyPressed(KEY_INPUT_A) && !Input::IsKeyPressed(KEY_INPUT_D);
			if (noInput) {
				rigid_ptr->SetVelocity({ 0.0f, rigid_ptr->velocity().y });
			}
		}

}
