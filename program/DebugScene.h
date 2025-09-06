#pragma once
#include"sceneBase.h"
#include"TestPlayer.h"
#include"MapManager.h"
#include"Camera.h"

/// <summary>
/// デバック用スクリーン
/// </summary>
class SceneDebug :public Scene{
	std::shared_ptr<GameObject> player_;
	std::string map_data_path_ = "res/map/data/map_data.txt";
	std::string tutorial_map_data_ = "res/map/data/tutorial_map.txt";
	std::string boss_map_data_ = "res/map/data/boss_map.txt";


public:
	SceneDebug();
	void Update()override;
	void Render()override;
};