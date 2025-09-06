#pragma once
#include"MapData.h"
#include"Camera.h"
#include"TextureResource.h"
#include<unordered_map>
#include<memory>
#include"MapLoader.h"

class MapRender {
	//	�^�C���摜�̃R���N�V�����^
	using TexturePtr_map = std::unordered_map<int, std::shared_ptr<TextureResource>>;

	//	�`������邩�ǂ���
	bool isDraw(int num) {
		return num != 0 && num != 2;
	}
public:
	//	�^�C���摜��ǂݍ���
	void LoadTexture(const std::unordered_map<int, std::string>& tiles_file_path);


	void Render(const MapData& mapData);
private:
	TexturePtr_map tile_textures_;	//	�^�C���摜�̃R���N�V����
};