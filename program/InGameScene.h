#pragma once
#include"sceneBase.h"
#include<string>
#include"Player.h"
#include"TextureResource.h"



class InGameScene : public Scene {
	void Result();
	void ResultRender();

public:
	InGameScene();
	virtual ~InGameScene() = default;
	void Init();
	void Update() override;
	void Render() override;

	void ResetStage();
	void NextStage();
private:
	std::string bg_filePath_;
	std::shared_ptr<TextureResource> bg_;
	std::shared_ptr<TextureResource> grave_;
	std::shared_ptr<Player> player_;
	std::shared_ptr<GameObject> goal_;
	int stageNumber = 1;
	const int max_stateNum = 1;
	int resetCount = 0;
	std::string mapDataFile;
	bool isResult = false;
};
