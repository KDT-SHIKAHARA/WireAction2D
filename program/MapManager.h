#pragma once
#include<vector>
#include<memory>
#include"MapRender.h"
#include"MapData.h"
#include"MapResHandle.h"
#include"singleton.h"

class GameObject;
class MapManager:public Singleton<MapManager>{
	friend class Singleton<MapManager>;

	MapManager() = default;
	virtual ~MapManager() = default;


	//	�`��
	MapRender render_;

	//	�f�[�^
	MapData mapData_;

	//	�n���h��
	TileTextureRegistry registry_;

	//	�n���h�����i�[���Ă�t�@�C���̃p�X
	std::string handle_path_ = "res/map/handle/data.xml";
	std::string map_data_path_ = "res/map/data/map_data.txt";
	std::string tutorial_map_data_ = "res/map/data/tutorial_map.txt";
	std::string boss_map_data_ = "res/map/data/boss_map.txt";
public:
	//	���̃}�b�v�ԍ����_���[�W��GameObj���H�炤�ԍ�������


	//	GameObject�Ƃ̓����蔻��
	void CheckCollision(const std::vector<std::shared_ptr<GameObject>>& gameObjs);

	//	�_�Ƃ̓����蔻��
	bool CheckPointHit(const Vector2D<float>& anchor_pos);

	//	
	bool CheckAABB(std::shared_ptr<GameObject> gameObj);

	//	�}�b�v�f�[�^�̓Ǎ�
	void Load(const std::string& map_data);

	//	�`��
	void Render();

	Vector2D<int> ChipNum() {
		return Vector2D<int> { mapData_.GetMapW(), mapData_.GetMapH() };
	}

	int ChipSize() {
		return mapData_.GetTileSize();
	}


};