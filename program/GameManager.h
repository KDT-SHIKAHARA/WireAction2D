#pragma once
#pragma once
#include<memory>
#include"sceneBase.h"
#include"RemFPS.h"


class GameManager {
	CRemFPS fps;						//	fps固定＆表示
	std::unique_ptr<Scene> scenePtr;	//	各画面基底ポインタ

	GameManager();
	virtual ~GameManager();

	void update();
	void render();
public:
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	static GameManager& Instance() {
		static  GameManager instance;
		return instance;
	}

	//	sceneのインスタンス生成＆変更
	template<typename T>
	void CreateScene() {
		scenePtr = std::make_unique<T>();
	}

	//	ゲームループ
	void GameLoop();
};