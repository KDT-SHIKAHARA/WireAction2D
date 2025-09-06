#pragma once
#include"SoundResource.h"
#include"flag.h"
#include"SoundType.h"
#include<memory>


class Sound {
	using Resource = std::shared_ptr<SoundResource>;
	Resource resource_;		//	音ハンドル
	int volume_;			//	音量
	SoundType type_;			//	サウンドの種別
	Flag isPlaying_;			//	再生フラグ

public:
	Sound(const Resource& arg_resource,int volume, SoundType arg_type)
		:resource_(arg_resource),volume_(volume), type_(arg_type), isPlaying_(false) { }
	virtual ~Sound() = default;

	//	再生
	void Play(int PlayType);

	//	停止
	void Stop();

	//	再生フラグ
	bool IsPlay()const;

	//	音量設定
	void SetVolume(float arg_volumeRatio);

	SoundType type()const { return type_; }
	

};