#include "SoundManager.h"
#include"SoundResourceMng.h"
#include"DxLib.h"


std::shared_ptr<Sound> SoundMgr::Add(const std::string& filePath, int volume, SoundType arg_type){
	//	検索
	auto ite = soundContainer.find(filePath);
	//	コンテナ内にあればその音クラスポインタを返す
	if (ite != soundContainer.end()) {
		return ite->second;
	}

	auto newSound = create(filePath, volume, arg_type);
	soundContainer.insert(std::make_pair(filePath, newSound));
	return newSound;
}

/// <summary>
/// コレクション内のすべての要素を削除
/// </summary>
void SoundMgr::ChangeVolumeAll(){

}



/// <summary>
/// ポインタを生成
/// </summary>
/// <param name="filePath"> ファイルパス </param>
/// <param name="volume">	音量			</param>
/// <param name="arg_type">	属性			</param>
/// <returns>				ポインタ		</returns>
std::shared_ptr<Sound> SoundMgr::create(const std::string& filePath, int volume, SoundType arg_type){
	std::shared_ptr<Sound> tmp_sound =
		std::make_shared<Sound>(SoundResourceMgr::Instance().GetSound(filePath), volume, arg_type);
	return tmp_sound;
}
