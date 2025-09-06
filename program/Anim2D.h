#pragma once
#include<memory>
#include<vector>
#include<string>


#include"TextureResource.h"
#include"flag.h"

/// <summary>
/// �����̉摜�ŃA�j���[�V�������s��
/// component�ɂ���ƊǗ��ʓ|�Ȃ̂ł���̃C���X�^���X���Ǘ�����component������GameObject���ɍ����j�ɂ��܂��B
/// 2025.8.13
/// 
/// @ �A�j���[�V�����ɕK�v�ȉ摜�n���h���̊Ǘ�
/// @ �t���[���̐؂�ւ�����
/// @ �Đ���Ԃ̐ݒ�Ƃ���ɉ������Đ�����
/// @ 
/// </summary>
class Anim2D {

	//	�t���[����i�߂�
	void stepFrame();

public:
	//	�Đ����[�h
	enum class PlayMode {
		Loop,		//	0-1-2-0-1-2... �Ń��[�v
		Ones,		//	0-1-2 �Œ�~
	};

	//-----���[�h�n-----
	void LoadFrames(const std::string& path, int num_frames, float duration = 0.2f,float exRate = 1.0f, PlayMode playMode = PlayMode::Loop);

	//-----------------
	//	�Đ�����
	void Play() { isPlaying_ = true; }
	void Pause() { isPlaying_ = false; }
	void Stop() { isPlaying_ = false;  current_ = 0; }
	void SetPlayMode(PlayMode mode) { mode_ = mode; }
	void SetDrawScale(float scale);
	void SetRotation(float rad) { rotation_rad_ = rad; }
	void Reset() {
		current_ = 0;
		elapsed_ms_ = 0;
		isFinished_ = false;
 		isPlaying_ = true;
	}

	void Update();
	void Render(float x,float y);
private:
	std::vector< std::shared_ptr<TextureResource>> frames_;	//	�`�悷��摜���X�g

	//	�Đ�����
	double elapsed_ms_ = 0;				//	���݂̃t���[���̌o�ߎ���
	float duration_ms_ = 0.2f;			//	�t���[����؂�ւ��鎞��
	int current_ = 0;					//	���ݍĐ����̃t���[���ԍ�
	PlayMode mode_ = PlayMode::Loop;	//	�Đ����[�h

	//	�`��p�����[�^�[
	float draw_scale_ = 1.0f;	//	�k����
	float rotation_rad_ = 0.f;	//	�\���̉�]


	Flag isPlaying_ = false;		//	�Đ��t���O
	Flag isFinished_ = false;		//	��񂫂�̏������I������̂�

public:
	Flag isFlip_ = false;		//	���]�����邩�ǂ���

};