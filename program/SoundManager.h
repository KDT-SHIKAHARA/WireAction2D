#pragma once
#include"Sound.h"
#include<memory>
#include<map>
#include<string>



/// <summary>
/// ���ʒ����Ȃǂ̈ꊇ�ōs����悤�ɂ���
/// </summary>
class SoundMgr {
	using SoundTable = std::map<std::string, std::shared_ptr<Sound>>;

	//	�Ǘ����鉹�̃R���N�V����
	SoundTable soundContainer;

	//	�{�����[���́A�ʂ̉��ʂ̊����ŕς���
	struct Volume {
		float master;	
		float bgm;		
		float se;
		//	�{�C�X����Βǉ�
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

	//	�ǉ�
	std::shared_ptr<Sound> Add(const std::string& filePath, int volume, SoundType arg_type);


	//	���ʂ̈ꊇ�ύX
	void ChangeVolumeAll();

	//	���ׂĂ̒�~
private:
	SoundMgr() = default;
	virtual ~SoundMgr() = default;

	//	���ʂ̕ύX


	//	�ǉ�
	std::shared_ptr<Sound> create(const std::string& filePath, int volume, SoundType arg_type);

};