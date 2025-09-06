#include"MapLoader.h"
#include<fstream>
#include<sstream>
#include<unordered_set>
#include<stdexcept>
#include<cassert>

/// <summary>
/// ��������u�C�v�̑O�ŋ�؂���Tile�N���X�Ɋi�[����B
/// </summary>
/// <param name="str"> �t�@�C������ǂݍ���1�s�P�� </param>
/// <param name="delimiter"> ��؂镶�� </param>
/// <returns> 1�s�P�ʂ�Tile�N���X�B </returns>
std::vector<Tile> MapLoader::split(const std::string& str, char delimiter) {
	std::vector<Tile> tmp_row;	
	std::istringstream tmp_csvLine(str);
	std::string tmp_strBuf;	

	while (std::getline(tmp_csvLine,tmp_strBuf,delimiter)){
		int tmp_map_num = std::stoi(tmp_strBuf);
		//	�o�O���Ă��ӏ��͂���
		assert(tmp_map_num < TileType::Max);
		if (tmp_map_num >= TileType::Max) throw std::out_of_range("MapLoader::split: �ǂݍ��񂾃}�b�v�ԍ����ő�l���z���Ă��܂�");
		tmp_row.push_back(
			{ tmp_map_num,TileShape::Rect, CheckCollisionFlag(tmp_map_num) });
	}

	return tmp_row;
}

/// <summary>
/// �����蔻������邩�ǂ����𔻒肷�郁�\�b�h
/// </summary>
/// <param name="map_num"></param>
/// <returns></returns>
bool MapLoader::CheckCollisionFlag(int map_num){
	//	�R���e�i�ɓ����蔻�������v�f���i�[
	static const std::unordered_set<int> conllidable_nums = { 1,2};

	//	�R���e�i���ɂ����true�@�Ȃ����flase
	return conllidable_nums.count(map_num) > 0;
}

/// <summary>
/// �t�@�C������}�b�v�f�[�^��ǂݍ����Tile�N���X�B�Ɋi�[����
/// </summary>
/// <param name="filepath"> �t�@�C���̃t���p�X </param>
/// <returns> �}�b�v�f�[�^���i�[����Tile�N���X�̃R���N�V������Ԃ� </returns>
std::vector<std::vector<Tile>> MapLoader::Load(const std::string& filepath) {
	std::ifstream file(filepath);
	std::vector<std::vector<Tile>> tmp_map_data;
	std::string tmp_line_str;

	//	�S�Ď擾	
	while (std::getline(file, tmp_line_str)) {
		tmp_map_data.push_back(split(tmp_line_str));
	}
	
	//	�}�b�v�f�[�^���i�[����Tile�̃R���N�V������Ԃ�
	return tmp_map_data;
}
