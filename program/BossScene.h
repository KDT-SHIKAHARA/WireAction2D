#pragma once
#include"sceneBase.h"

/// <summary>
/// ボスのステージ
/// </summary>
class BossStage : public Scene {
	std::shared_ptr<GameObject> player_;
	std::string boss_map_data_ = "res/map/data/boss_map.txt";

public:
	BossStage();
	void Update()override;
	void Render()override;
};