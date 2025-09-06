#pragma once
#pragma once
#include<memory>
#include"sceneBase.h"
#include"RemFPS.h"


class GameManager {
	CRemFPS fps;						//	fps�Œ聕�\��
	std::unique_ptr<Scene> scenePtr;	//	�e��ʊ��|�C���^

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

	//	scene�̃C���X�^���X�������ύX
	template<typename T>
	void CreateScene() {
		scenePtr = std::make_unique<T>();
	}

	//	�Q�[�����[�v
	void GameLoop();
};