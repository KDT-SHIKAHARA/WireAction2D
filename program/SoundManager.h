#pragma once
#include"Sound.h"
#include<memory>
#include<map>
#include<string>



/// <summary>
/// 音量調整などの一括で行えるようにする
/// </summary>
class SoundMgr {
	using SoundTable = std::map<std::string, std::shared_ptr<Sound>>;

	//	管理する音のコレクション
	SoundTable soundContainer;

	//	ボリュームは、個別の音量の割合で変える
	struct Volume {
		float master;	
		float bgm;		
		float se;
		//	ボイスあれば追加
		Volume(float arg_master = 1.0,float arg_bgm =1.0f,float arg_se = 1.0f)
			:master(arg_master), bgm(arg_bgm), se(arg_se){ }
	};




public:
	SoundMgr(const SoundMgr&) = delete;
	SoundMgr& operator=(const SoundMgr&) = delete;

	static SoundMgr& Instance() {
		static SoundMgr instance;
		return instance;
	}

	//	追加
	std::shared_ptr<Sound> Add(const std::string& filePath, int volume, SoundType arg_type);


	//	音量の一括変更
	void ChangeVolumeAll();

	//	すべての停止
private:
	SoundMgr() = default;
	virtual ~SoundMgr() = default;

	//	音量の変更


	//	追加
	std::shared_ptr<Sound> create(const std::string& filePath, int volume, SoundType arg_type);

};