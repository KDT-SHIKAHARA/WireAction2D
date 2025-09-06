#pragma once
#include<vector>
#include<string>
#include"Tile.h"

/// <summary>
/// �}�b�v�f�[�^�̓Ǎ��ƃ}�b�v�f�[�^�̒��g�������Ă���Tile�N���X�̃R���N�V�����̊Ǘ�
/// </summary>
class MapData final{
	//	�ʃG���A�X
	using Tiles = std::vector<std::vector<Tile>>;

public:
	MapData();
	virtual ~MapData() = default;

	//	�}�b�v�f�[�^�̓Ǎ�
	void LoadMapData(const std::string& filePath);

	//	�^�C���̎Q�Ƃ��擾�i�ύX�s�j
	const Tile& GetTile(int index_x, int index_y) const ;

	//	�}�b�v�T�C�Y�̎擾
	int GetMapW()const { return map_max_w_; }
	int GetMapH()const { return map_max_h_; }

	//	�^�C���̃T�C�Y�擾
	int GetTileSize()const { return tile_size_; }

	/// <summary>
	/// �}�b�v�̃C���f�b�N�X��������
	/// </summary>
	/// <param name="map_x"> index X </param>
	/// <param name="map_y"> index Y </param>
	/// <returns> true: �}�b�v�� false: �}�b�v�O </returns>
	bool IsInMap(int map_x,int map_y){
		return !(map_x < 0 || map_y < 0 ||
			map_x >= map_max_w_ || map_y >= map_max_h_);
	}

private:

	int tile_size_;

	int map_max_w_;	//	�}�b�v�̉��̍ő吔
	int map_max_h_;	//	�}�b�v�̏c�̍ő吔

	Tiles tiles_;	//	�^�C���̃R���N�V����
};