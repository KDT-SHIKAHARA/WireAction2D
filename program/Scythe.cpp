#include<cmath>
#include "Scythe.h"
#include "Time.h"
#include "GameObjectMgr.h"
#include "GameObject.h"
#include "input.h"
#include "Camera.h"

void Scythe::Start() 
{
	active_ = true;
	reachedTarget_ = false;
	attack_time_ = 0;
	wait_time_ = 0;
	pos_ = GetGameObj()->transform.WorldPosition();
	auto targets = GameObjMgr::Instance().GetGameObjWithTag(Tag::GetString(TagType::Player));
	for (const auto& player : targets) {
		target_ = player->transform.WorldPosition();
	}
}


void Scythe::Update()
{

#ifdef _DEBUG
	if(Input::IsKeyOn(KEY_INPUT_Y)){
		Start();
	}
#endif // _DEBUG


	if (!active_)return;


	//	�f���^�^�C���擾
	auto dt = Time::deltaTime();

	//	�U���𖳌� �Ȃ�
	if (!reachedTarget_) {
		//	�ړ��x�N�g�����擾����
		auto dir = target_ - pos_;
		//	�������擾
		auto len = dir.GetLength();

		//	�������܂�����������
		if (len > k_stopDistance_) {

			GetGameObj()->transform.MoveToTarget(target_,(float)(k_speed_ * dt));
			pos_ = GetGameObj()->transform.WorldPosition();

			////	���K��
			//dir.Normalize();

			////	�ړ�
			//pos_ += dir * (float)(k_speed_ * dt);

		}
		//	�v���C���[�̋߂��Ȃ�
		else {
			//	�t���O�𗧂�
			reachedTarget_ = true;

			//	���ߎ��ԃZ�b�g
			wait_time_ = k_wait_time_;
		}

		////	���W�X�V
		//GetGameObj()->transform.SetWorldPosition(pos_);

	}
	//	�L����Ԃŗ��ߏ�ԂȂ�
	else if (wait_time_ > 0.0) {
		//	���ߎ��Ԃ����炵��
		wait_time_ -= dt;

		//	�҂����Ԃ��I�����Ă�����
		if (wait_time_ <= 0.0) {
			//	�U�����ԃZ�b�g
			attack_time_ = k_attackDuratuin_;
		}
	}
	//	�L����ԂōU����ԂȂ�
	else if (attack_time_ > 0.0) {
		//	�U�����Ԃ����炵��
		attack_time_ -= dt;

		//	�U�����Ԃ��I�����Ă�����
		if (attack_time_ <= 0.0) {
			//	�L���t���O��܂�
			active_ = false;
		}
	}
}

void Scythe::Render()
{
	if (!active_) return;

	// �J�����ʒu�i��F�J���������[���h�̂ǂ������Ă��邩�j
	Vector2D<float> camPos = Camera::Instance().position();
	Vector2D<float> camOffset = Camera::Instance().area_size();

	// ���[���h���W �� �X�N���[�����W
	Vector2D<float> screenPos = pos_ - camPos + camOffset / 2;

	if (attack_time_ > 0.0) {
		// --- �U���͈́i�Ԃ��~�j ---
		DrawCircle((int)screenPos.x, (int)screenPos.y, (int)k_radius_, GetColor(255, 0, 0), TRUE);
	}
	else if (reachedTarget_ && wait_time_ > 0.0) {
		// --- ���߉��o�i�����������Ă����j ---
		double t = 1.0 - (wait_time_ / k_wait_time_);
		int radius = (int)(k_radius_ * (1.0 - t * 0.7));
		int alpha = (int)(128 + 127 * t);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawCircle((int)screenPos.x, (int)screenPos.y, radius, GetColor(255, 200, 100), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// �O���Ɍ��̃����O
		DrawCircle((int)screenPos.x, (int)screenPos.y, radius + 10, GetColor(255, 255, 200), FALSE);
	}
	else {
		// --- �ړ����̃{�X�i�D�F�̉~�ŕ`��j ---
		DrawCircle((int)screenPos.x, (int)screenPos.y, 16, GetColor(200, 200, 200), TRUE);
	}
}

