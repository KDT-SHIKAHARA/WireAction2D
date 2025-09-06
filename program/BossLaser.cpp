#include<algorithm>
#include "BossLaser.h"
#include "BossState.h"
#include "BossStateController.h"
#include "Time.h"
#include "Camera.h"
#include "dxlib.h"
#include "GetColor.h"
#include "input.h"
#include "SystemConfig.h"

void Laser::start()
{
	frame_ = 0;
	active_ = true;
	target_pos_ = Vector2D<float>{ (float)WINDOW_W / 2, (float)WINDOW_H / 2 - 200 };
}

void Laser::Update()
{
	auto stateCo = GetGameObj()->GetComponent<BossStateController>();
	auto state = GetGameObj()->GetComponent<BossStateComp>();
	if (!stateCo || !state)return;

	//	�\�Ȏ�
	if (stateCo->CanLaser()) {
		stateCo->RequestLaser();
	}

#ifdef _DEBUG
	if (Input::IsKeyOn(KEY_INPUT_T)) {
		start();
	}
#endif // !_DEBUG


	//	����
	if (state->GetState() != BossState::Laser) {
		active_ = false;
		return;
	}
	
	//	���Ԍo��
	frame_ += Time::deltaTime();

	//	�o�ߎ��Ԃɉ����āA��Ԃ̔���
	//	�ҋ@���Ԗ���
	if (frame_ < k_wait_max_) {
		mode_ = State::wait;
	}
	//	�ő厞�ԂɒB���Ă����珈���̏I��
	else if (frame_ > k_frame_max_) {
		active_ = false;
		mode_ = State::finish;
	}
	else {
		mode_ = State::laser;
	}

	//	�L���̎��X�W
	if (active_) {
		//	�{�X�̈ړ�
		GetGameObj()->transform.MoveToTarget(target_pos_, mov_speed_);

		//	�J�������W���瓖���蔻������郏�[���h���W���擾����
		base_pos_ = Camera::Instance().position() - Camera::Instance().area_size() / 2.f;
		area_size_ = { Camera::Instance().area_size().x,200 };
	}

	auto camPos = Camera::Instance().position();
	auto camSize = Camera::Instance().area_size();

	// ���[���h���W�ł̍U���G���A
	base_pos_.x = camPos.x - camSize.x / 2.0f;
	base_pos_.y = camPos.y + camSize.y / 2.0f - 200; // ��ʉ�����200px
	area_size_ = { camSize.x, 200 };

	// �X�N���[�����W�ɕϊ�
	screen_pos_.x = base_pos_.x - (camPos.x - camSize.x / 2.0f);
	screen_pos_.y = base_pos_.y - (camPos.y - camSize.y / 2.0f);


	//	�I������
	//	���Z�b�g���鍀�ڂ̏���������



}

void Laser::Render()
{
	if (!active_)return;

	switch (mode_)
	{
	case Laser::State::wait:
	{
		// �Ԃ��������{�_�Łisin�ŃA���t�@��h�炷�j
		int alpha = (int)(128 + 127  * sin(frame_ * 0.2));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(screen_pos_.x, screen_pos_.y, screen_pos_.x + area_size_.x, screen_pos_.y + area_size_.y,
			RED, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
		break;
	case Laser::State::laser:
		DrawBox(screen_pos_.x, screen_pos_.y, screen_pos_.x + area_size_.x, screen_pos_.y + area_size_.y,
			BLACK, TRUE);
	{


	}
		break;
	case Laser::State::finish:
		break;
	default:
		break;
	}

}
