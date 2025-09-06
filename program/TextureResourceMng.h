#pragma once
#include<map>
#include<string>
#include<memory>
#include "TextureResource.h"
#include "DxLib.h"

//	2025.5.2


#define _TEX_RES_MGR(file_path) TextureResourceMgr::Instance().GetTexture(file_path)

/// <summary>
/// 画像の読み込みと管理をする。
/// factoryの要素をもつmanagerのような感じなのでstaticではない
/// </summary>
class TextureResourceMgr {
private:
	//	画像をプール化して検索できるように (K,V) = (fileName, Texture)
	std::map <std::string, std::shared_ptr<TextureResource>> textureContainer;
	
	/// 画像クラスの生成
	/// <param name="fileName">	ファイルのフルパス			</param>
	/// <returns>				画像クラスのshareポインタ	</returns>		
	std::shared_ptr<TextureResource> createTexture(std::string fileName){
		//	画像の読込処理
		int handle = LoadGraph(fileName.c_str());
		//	画像クラスの生成
		auto newTexture = std::make_shared<TextureResource>(handle);
		//	作成した画像クラスを返す。
		return newTexture;
	}


	TextureResourceMgr() = default;
	virtual ~TextureResourceMgr() = default;

public:
	TextureResourceMgr(const TextureResourceMgr&) = delete;
	TextureResourceMgr& operator=(const TextureResourceMgr&) = delete;

	//	インスタンスの生成
	static TextureResourceMgr& Instance() {
		static TextureResourceMgr instance;
		return instance;
	}

	//	画像クラスの取得
	std::shared_ptr<TextureResource> GetTexture(std::string fileName) {
		//	ファイル名で画像検索
		auto ite = textureContainer.find(fileName);

		//	コンテナ内にあればその画像クラスポインタを返す。
		if (ite != textureContainer.end()) {
			return ite->second;
		}
		
		//	コンテナ内になければ新たに画像クラスを生成してコンテナに登録
		auto newTexture = createTexture(fileName);

		textureContainer.insert(std::make_pair(fileName, newTexture));

		//	作成した画像クラスを返す
		return newTexture;
	}
};