#include "MapData.h"
#include<stdexcept>
#include"MapLoader.h"

//	������
MapData::MapData():tile_size_(32), map_max_w_(0), map_max_h_(0){
}

/// <summary>
/// �t�@�C���Ǎ��N���X�̓Ǎ����\�b�h������āA�}�b�v�f�[�^����ꂽTiles�^�̃I�u�W�F�N�g��Ԃ�
/// </summary>
/// <param name="filePath"> �}�b�v�f�[�^�������Ă���t�@�C�� </param>
void MapData::LoadMapData(const std::string& filePath){
	//	�Ǎ����\�b�h
	tiles_ = MapLoader::Load(filePath);

	////	�T�C�Y�擾
	map_max_w_ = tiles_[0].size();
	map_max_h_ = tiles_.size();

}

/// <summary>
/// �w�肵���C���f�b�N�X�̃^�C����const�Q�Ƃ�Ԃ��B
/// �C���f�b�N�X���͈͊O�Ȃ��O��f��
/// </summary>
/// <param name="arg_x"> ���v�f���̃C���f�b�N�X </param>
/// <param name="arg_y"> ���v�f���̃C���f�b�N�X </param>
/// <returns></returns>
const Tile& MapData::GetTile(int index_x, int index_y) const {
	if (index_x < 0 || index_y < 0 || index_x >= map_max_w_ || index_y >= map_max_h_)
	{
		return Tile{};
	}
	return  tiles_[index_y][index_x];
}
