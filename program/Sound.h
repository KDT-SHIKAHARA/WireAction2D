#pragma once
#include"SoundResource.h"
#include"flag.h"
#include"SoundType.h"
#include<memory>


class Sound {
	using Resource = std::shared_ptr<SoundResource>;
	Resource resource_;		//	���n���h��
	int volume_;			//	����
	SoundType type_;			//	�T�E���h�̎��
	Flag isPlaying_;			//	�Đ��t���O

public:
	Sound(const Resource& arg_resource,int volume, SoundType arg_type)
		:resource_(arg_resource),volume_(volume), type_(arg_type), isPlaying_(false) { }
	virtual ~Sound() = default;

	//	�Đ�
	void Play(int PlayType);

	//	��~
	void Stop();

	//	�Đ��t���O
	bool IsPlay()const;

	//	���ʐݒ�
	void SetVolume(float arg_volumeRatio);

	SoundType type()const { return type_; }
	

};