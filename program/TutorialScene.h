#pragma once
#include "sceneBase.h"

class Player;

class Tutorial : public Scene {


public:
	Tutorial();
	void Update()override;
	void Render()override;

private:
	std::shared_ptr<Player> player_;
	std::string tutorial_map_data_ = "res/map/data/tutorial_map.txt";

};