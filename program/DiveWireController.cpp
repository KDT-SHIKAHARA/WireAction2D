#include "DiveWireController.h"
#include "GameObject.h"
#include "PlayerStateController.h"
#include "input.h"
#include "dive wire.h"
#include "RigidbodyComp.h"

/// <summary>
/// ���ˉ\��Ԃ̔���Ɠ��͂̔���ADiveWire�̗L����
/// </summary>
void DiveWireController::Update() {
	auto state = GetGameObj()->GetComponent<StateController>();
	if (!state)return;
	if (!state->CanDiveWire()) return;

	//	���͔���
	if (Input::IsMouseOn(MOUSE_INPUT_LEFT)) {
		auto diveWire = GetGameObj()->GetComponent<DiveWire>();
		auto rigid = GetGameObj()->GetComponent<RigidbodyComp>();
		if (!diveWire || !rigid)return;
		state->RequestDiveWire();	//	�ύX���N�G�X�g
		diveWire->Start();			//	�ړ��x�N�g���Z�b�g
		rigid->isStatic_.Set(true);	//	�d�͒�~
		rigid->SetVelocity(Vector2D<float>{0, 0});

	}	
}