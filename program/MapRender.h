#pragma once
#include"MapData.h"
#include"Camera.h"
#include"TextureResource.h"
#include<unordered_map>
#include<memory>
#include"MapLoader.h"

class MapRender {
	//	タイル画像のコレクション型
	using TexturePtr_map = std::unordered_map<int, std::shared_ptr<TextureResource>>;

	//	描画をするかどうか
	bool isDraw(int num) {
		return num != 0 && num != 2;
	}
public:
	//	タイル画像を読み込む
	void LoadTexture(const std::unordered_map<int, std::string>& tiles_file_path);


	void Render(const MapData& mapData);
private:
	TexturePtr_map tile_textures_;	//	タイル画像のコレクション
};