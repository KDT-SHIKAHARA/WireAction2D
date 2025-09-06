#include "SoundManager.h"
#include"SoundResourceMng.h"
#include"DxLib.h"


std::shared_ptr<Sound> SoundMgr::Add(const std::string& filePath, int volume, SoundType arg_type){
	//	����
	auto ite = soundContainer.find(filePath);
	//	�R���e�i���ɂ���΂��̉��N���X�|�C���^��Ԃ�
	if (ite != soundContainer.end()) {
		return ite->second;
	}

	auto newSound = create(filePath, volume, arg_type);
	soundContainer.insert(std::make_pair(filePath, newSound));
	return newSound;
}

/// <summary>
/// �R���N�V�������̂��ׂĂ̗v�f���폜
/// </summary>
void SoundMgr::ChangeVolumeAll(){

}



/// <summary>
/// �|�C���^�𐶐�
/// </summary>
/// <param name="filePath"> �t�@�C���p�X </param>
/// <param name="volume">	����			</param>
/// <param name="arg_type">	����			</param>
/// <returns>				�|�C���^		</returns>
std::shared_ptr<Sound> SoundMgr::create(const std::string& filePath, int volume, SoundType arg_type){
	std::shared_ptr<Sound> tmp_sound =
		std::make_shared<Sound>(SoundResourceMgr::Instance().GetSound(filePath), volume, arg_type);
	return tmp_sound;
}
