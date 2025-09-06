#pragma once
#include<string>
#include<unordered_map>

/// <summary>
/// �t�@�C���p�X�̊Ǘ�
/// </summary>
class TileTextureRegistry {

	enum class TileType {
		None,
		Grass,
		Sky,
	};

public:


	//	�t�@�C���p�X�̓Ǎ�
	TileTextureRegistry() {
		tiles_file_path_[static_cast<int>(TileType::Grass)] =
			"res/map/texture/grass.png";

		tiles_file_path_[static_cast<int>(TileType::Sky)] =
			"res/map/texture/default.png";

	}

	//	xml�t�@�C������p�X��ǂݍ���
	//	true: �Ǎ����� false: �Ǎ����s
	void LoadFilesPath(const std::string& xml_path);

	//	�t�@�C���p�X���Z�b�g����
	 
	//	�^�C��ID�ɑΉ�����t�@�C���p�X��Ԃ�
	//	������Ȃ�������󕶎���Ԃ��B
	//	�f�t�H���g�t�@�C���p�X��ݒ肵�Ă�����
	std::string GetPath(int tile_id)const;

	std::unordered_map<int, std::string> tiles_file_path() { return tiles_file_path_; }

private:
	std::unordered_map<int, std::string> tiles_file_path_;
	std::string tiles_base_path_;
};