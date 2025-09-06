#pragma once
#include<map>
#include<string>
#include<memory>
#include"DxLib.h"
#include"SoundResource.h"

class SoundResourceMgr {
private:
	//	検索テーブル
	std::map<std::string, std::shared_ptr<SoundResource>> soundContainer;
	
	//	生成
	std::shared_ptr<SoundResource> createSound(std::string fileName) {
		//	読み込み処理
		int handle = LoadSoundMem(fileName.c_str());
		//	音クラス作成
		auto newSound = std::make_shared<SoundResource>(handle);
		//	ポインタを返す。
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

	//	音ハンドルが格納されたクラスの取得、なければ作成
	std::shared_ptr<SoundResource> GetSound(std::string fileName) {
		//	ファイルで検索
		auto ite = soundContainer.find(fileName);
		//	コンテナ内にあればその音クラスポインタを返す
		if (ite != soundContainer.end()) {
			return ite->second;
		}

		//	なければ音クラスの作成
		auto newSound = createSound(fileName);
		soundContainer.insert(std::make_pair(fileName, newSound));
		//	作成した音クラスを返す
		return newSound;
	}

};
