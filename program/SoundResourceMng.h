#pragma once
#include<map>
#include<string>
#include<memory>
#include"DxLib.h"
#include"SoundResource.h"

class SoundResourceMgr {
private:
	//	�����e�[�u��
	std::map<std::string, std::shared_ptr<SoundResource>> soundContainer;
	
	//	����
	std::shared_ptr<SoundResource> createSound(std::string fileName) {
		//	�ǂݍ��ݏ���
		int handle = LoadSoundMem(fileName.c_str());
		//	���N���X�쐬
		auto newSound = std::make_shared<SoundResource>(handle);
		//	�|�C���^��Ԃ��B
		return newSound;
	}

	SoundResourceMgr() = default;
	virtual ~SoundResourceMgr() = default;

public:
	SoundResourceMgr(const SoundResourceMgr&) = delete;
	SoundResourceMgr& operator=(const SoundResourceMgr&) = delete;

	static SoundResourceMgr& Instance() {
		static SoundResourceMgr instance;
		return instance;
	}

	//	���n���h�����i�[���ꂽ�N���X�̎擾�A�Ȃ���΍쐬
	std::shared_ptr<SoundResource> GetSound(std::string fileName) {
		//	�t�@�C���Ō���
		auto ite = soundContainer.find(fileName);
		//	�R���e�i���ɂ���΂��̉��N���X�|�C���^��Ԃ�
		if (ite != soundContainer.end()) {
			return ite->second;
		}

		//	�Ȃ���Ή��N���X�̍쐬
		auto newSound = createSound(fileName);
		soundContainer.insert(std::make_pair(fileName, newSound));
		//	�쐬�������N���X��Ԃ�
		return newSound;
	}

};
