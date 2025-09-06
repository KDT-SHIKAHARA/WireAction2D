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


	//	描画
	MapRender render_;

	//	データ
	MapData mapData_;

	//	ハンドル
	TileTextureRegistry registry_;

	//	ハンドルを格納してるファイルのパス
	std::string handle_path_ = "res/map/handle/data.xml";
	std::string map_data_path_ = "res/map/data/map_data.txt";
	std::string tutorial_map_data_ = "res/map/data/tutorial_map.txt";
	std::string boss_map_data_ = "res/map/data/boss_map.txt";
public:
	//	そのマップ番号がダメージをGameObjが食らう番号か判定


	//	GameObjectとの当たり判定
	void CheckCollision(const std::vector<std::shared_ptr<GameObject>>& gameObjs);

	//	点との当たり判定
	bool CheckPointHit(const Vector2D<float>& anchor_pos);

	//	
	bool CheckAABB(std::shared_ptr<GameObject> gameObj);

	//	マップデータの読込
	void Load(const std::string& map_data);

	//	描画
	void Render();

	Vector2D<int> ChipNum() {
		return Vector2D<int> { mapData_.GetMapW(), mapData_.GetMapH() };
	}

	int ChipSize() {
		return mapData_.GetTileSize();
	}


};