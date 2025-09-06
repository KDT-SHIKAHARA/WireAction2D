#include "dive wire.h"
#include "MapManager.h"
#include "input.h"
#include "GameObject.h"
#include "PlayerStateController.h"
#include "Time.h"
#include "dxlib.h"
#include "GetColor.h"
#include "ColliderComp.h"
#include "RigidbodyComp.h"
#include "Camera.h"

DiveWire::DiveWire()
{
}

void DiveWire::Update()
{
	//	��~���āA�ړ��Ȃǂ��ł��Ȃ���ԂŐݒu����܂ōs���̂�
	// ���W�̍X�V�͈�U�Ȃ���

	
	////	���W�̎擾
	//gameObjPos_ = GetGameObj()->transform.WorldPosition();

	//	���̏�Ԃ�����
	auto state = GetGameObj()->GetComponent<PlayerStateComp>();
	auto rigid = GetGameObj()->GetComponent<RigidbodyComp>();

	if (!state || !rigid)return;
	if (state->GetState() != _P_STATE::dive) return;

	//	���C���[�̒��f����
	if (Input::IsKeyOn(KEY_INPUT_SPACE)) {
		isFinished_ = true;
	}

	//	�A���J�[���˂܂ł̑҂�����
	if (chargeFrame_ < kChargeFrameMax_) {
		chargeFrame_ += Time::deltaTime();
		return;
	}


	//	�A���J�[���ݒu����Ă��Ȃ�������ړ�����������
	if (!isAnchored) {
		//	���K�������ړ��x�N�g�� * �ړ����x(1�b�Ԃ̈ړ����x * 1F�̎���)
		anchorPos_ += (velocity_ * kAnchorSpeed_) * Time::deltaTime();
		

		//	�����̎擾
		length_ = Get2Distance<float>(anchorPos_, gameObjPos_);

		//	�ݒu���������
		if (MapManager::Instance().CheckPointHit(anchorPos_)) {
			isAnchored = true;
		}
		//	�ݒu����Ă��Ȃ��āA�������ő���z���Ă����珈�����I������
		else if (length_ >= kWireLength_) {
			isFinished_ = true;
		}
	}
	//	�A���J�[���ݒu����Ă�����
	else {

		////	����t���O���m�F true: �I��
		//if (isFinished_) {
		//	return;
		//}


		

		//	���݂̍��W�擾
		gameObjPos_ = (GetGameObj()->transform.WorldPosition() + (size_ / 2));

		//	�ړ��x�N�g���̌v�Z
		Vector2D<float> tmp_velocity = anchorPos_ - gameObjPos_;

		//	���K��
		tmp_velocity.Normalize();

		//	��_�Ԃ̋����ƒ����̌v�Z
		float length = Get2Distance(anchorPos_, gameObjPos_);

		//	�ړ�������ۂ̋���
		float gameObjSpeed = kGameObjectSpeed_;

		//	�ړ����鋗���ƃA���J�[�ƍ��W�̋����̌v�Z
		tmp_velocity = tmp_velocity * gameObjSpeed;

		//	�ړ��ʃZ�b�g
		rigid->SetVelocity(tmp_velocity);

		//	���C���[��Ԃ��������邩�ǂ����̔���
		if (MapManager::Instance().CheckAABB(GetGameObj())) {
			isFinished_ = true;
			rigid->SetVelocity({ 0,0 });
		}

	}
}

void DiveWire::Render()
{

	auto state = GetGameObj()->GetComponent<PlayerStateComp>();
	if (!state)return;
	if (state->GetState() != _P_STATE::dive) return;

	const auto& camera_pos = Camera::Instance().position();
	const auto& camera_size = Camera::Instance().area_size();

	float screen_gameObjX = gameObjPos_.x - camera_pos.x + camera_size.x / 2;
	float screen_gameObjY = gameObjPos_.y - camera_pos.y + camera_size.y / 2;
	float screen_anchorX = anchorPos_.x - camera_pos.x + camera_size.x / 2;
	float screen_anchorY = anchorPos_.y - camera_pos.y + camera_size.y / 2;

	DrawLineAA(screen_gameObjX, screen_gameObjY, screen_anchorX, screen_anchorY,
		SKYBLUE);

	//	�A���J�[���˂܂ł̎��Ԃ̎�����
	if (chargeFrame_ < kChargeFrameMax_) {
		
		//	����ɕ����Ă���^�̐����v�Z
		int cir_num = static_cast<int>(chargeFrame_ / (cir_one_frame));

		//	�`���[�W���̒e��`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		for (int i = 0; i <= cir_num; i++) {
			//	float angleDeg = (360.0f / cir_num) * i; 
			//	��cir_num �ɂ���Γ��삷�邽�тɂP������̊p�x���ω����Ȃ��̂�
			//	����܂����A�����ړI�ɂ������̂ق��������������̂ł���ɂ��܂��B
			//	by 2025.8.11�Ɏ������

			float angleDeg = (360.0f / cir_num) * i;
			//float angleDeg = (360.0f / cir_max_) * i;
			Vector2D<float> pos = GetPointFromAngle(gameObjPos_, cir_distance, angleDeg);
			
			// pos���X�N���[�����W�ɕϊ�
			float screen_posX = pos.x - camera_pos.x + camera_size.x / 2;
			float screen_posY = pos.y - camera_pos.y + camera_size.y / 2;


			DrawCircle(screen_posX, screen_posY, 5, BLUE, SKYBLUE);
			
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

/// <summary>
/// �ړ��x�N�g���̌v�Z
/// </summary>
void DiveWire::Start() {
	//auto size = GetGameObj()->GetComponent<ColliderComp>()->size();
	anchorPos_ = gameObjPos_ = (GetGameObj()->transform.WorldPosition() + (size_ / 2));
	Vector2D<float> mosue = { (float)Input::MouseX(),(float)Input::MouseY() };
	const Vector2D<float>& camera_pos = Camera::Instance().position();
	const Vector2D<float>& camera_size = Camera::Instance().area_size();
	Vector2D<float> world_mouse = camera_pos - camera_size / 2.f + mosue;
	velocity_ = world_mouse - gameObjPos_;
	velocity_.Normalize();
}


bool DiveWire::IsFinished() const
{
	return isFinished_;
}
