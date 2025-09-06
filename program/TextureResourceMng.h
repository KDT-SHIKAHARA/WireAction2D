#pragma once
#include<map>
#include<string>
#include<memory>
#include "TextureResource.h"
#include "DxLib.h"

//	2025.5.2


#define _TEX_RES_MGR(file_path) TextureResourceMgr::Instance().GetTexture(file_path)

/// <summary>
/// �摜�̓ǂݍ��݂ƊǗ�������B
/// factory�̗v�f������manager�̂悤�Ȋ����Ȃ̂�static�ł͂Ȃ�
/// </summary>
class TextureResourceMgr {
private:
	//	�摜���v�[�������Č����ł���悤�� (K,V) = (fileName, Texture)
	std::map <std::string, std::shared_ptr<TextureResource>> textureContainer;
	
	/// �摜�N���X�̐���
	/// <param name="fileName">	�t�@�C���̃t���p�X			</param>
	/// <returns>				�摜�N���X��share�|�C���^	</returns>		
	std::shared_ptr<TextureResource> createTexture(std::string fileName){
		//	�摜�̓Ǎ�����
		int handle = LoadGraph(fileName.c_str());
		//	�摜�N���X�̐���
		auto newTexture = std::make_shared<TextureResource>(handle);
		//	�쐬�����摜�N���X��Ԃ��B
		return newTexture;
	}


	TextureResourceMgr() = default;
	virtual ~TextureResourceMgr() = default;

public:
	TextureResourceMgr(const TextureResourceMgr&) = delete;
	TextureResourceMgr& operator=(const TextureResourceMgr&) = delete;

	//	�C���X�^���X�̐���
	static TextureResourceMgr& Instance() {
		static TextureResourceMgr instance;
		return instance;
	}

	//	�摜�N���X�̎擾
	std::shared_ptr<TextureResource> GetTexture(std::string fileName) {
		//	�t�@�C�����ŉ摜����
		auto ite = textureContainer.find(fileName);

		//	�R���e�i���ɂ���΂��̉摜�N���X�|�C���^��Ԃ��B
		if (ite != textureContainer.end()) {
			return ite->second;
		}
		
		//	�R���e�i���ɂȂ���ΐV���ɉ摜�N���X�𐶐����ăR���e�i�ɓo�^
		auto newTexture = createTexture(fileName);

		textureContainer.insert(std::make_pair(fileName, newTexture));

		//	�쐬�����摜�N���X��Ԃ�
		return newTexture;
	}
};