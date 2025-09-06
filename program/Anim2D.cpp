#define NOMINMAX

#include "Anim2D.h"
#include<sstream>
#include<fstream>
#include<cassert>
#include<algorithm>

#include"TextureResourceMng.h"
#include"Time.h"

/// <summary>
/// �t���[�������ɐi�߂�
/// �I�_�ɒB�����ꍇ�A�I��������̂��܂����[�v����̂��𔻒肵�ď����𕪊򍷂���
/// </summary>
void Anim2D::stepFrame()
{
	if (frames_.empty()) return;

	switch (mode_) {
	case PlayMode::Loop:
		current_ = (current_ + 1) % frames_.size();
		break;

	case PlayMode::Ones:
		if (current_ + 1 >= frames_.size()) {
			isPlaying_ = false;
			isFinished_ = true;
		}
		else {
			current_++;
		}
		break;
	}
}

/// <summary>
/// �A�Ԃ̉摜��ǂݍ���Ńt���[���\���̂��쐬����
/// </summary>
/// <param name="path"></param>
/// <param name="num_frames"></param>
/// <param name="duration"></param>
void Anim2D::LoadFrames(const std::string& path, int num_frames, float duration, float exRate, PlayMode playMode)
{
	for (int i = 0; i < num_frames; i++) {
		std::string filepath = path + std::to_string(i) + ".png";
		auto texture = TextureResourceMgr::Instance().GetTexture(filepath);
		assert(texture->GetHandle() != -1);
		frames_.push_back(texture);
	}
	duration_ms_ = duration;
	current_ = 0;
	elapsed_ms_ = 0.0;
	isPlaying_ = true;
	draw_scale_ = exRate;
	mode_ = playMode;

}



//	�`�旦�̐ݒ�
void Anim2D::SetDrawScale(float scale)
{
	scale = std::max(0.01f, scale);
	draw_scale_ = scale;
}

/// <summary>
/// animation�̐؂�ւ������Ȃ�
/// </summary>
void Anim2D::Update() {
	if (!isPlaying_ || frames_.empty()) return;


	elapsed_ms_ += Time::deltaTime();
	//	�z���Ă����炻�̕��t���[����i�߂�
	//	�t���[������������Ƃ��悤�ɉz���Ă��镪�S�Đi�߂�
	while (elapsed_ms_ >= duration_ms_) {
		elapsed_ms_ -= duration_ms_;	//	���Ԃ����炷
		stepFrame();//	�t���[����i�߂�
		if (!isPlaying_) break;	//	�o�ߎ��Ԃ̊֌W�Ŏ��܂ōs���Ă��܂����Ƃ��ɏI���ł���悤��
	}

}

void Anim2D::Render(float x, float y)
{
	if (frames_.empty())return;
	DrawRotaGraphF(x, y, draw_scale_, rotation_rad_, frames_[current_]->GetHandle(), TRUE, isFlip_);
}
