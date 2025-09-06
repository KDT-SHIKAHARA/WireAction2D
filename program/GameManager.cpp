#include "GameManager.h"
#include"DxLib.h"

#include "Time.h"
#include "input.h"

#include"DebugSceneNum.h"
#include"DebugLog.h"

#include"SystemConfig.h"
#include<cassert>
#include "Title.h"



//	������
GameManager::GameManager() {
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_W, WINDOW_H, WINDOW_C);
	SetMainWindowText("NoName");
	SetBackgroundColor(BACK_COLOR, BACK_COLOR, BACK_COLOR);

	errno_t err = DxLib_Init();
	assert(err != -1);
	SetDrawScreen(DX_SCREEN_BACK);

	//	�C���X�^���X����
	CreateScene<SCTitle>();

}

//	�I��
GameManager::~GameManager() {
	DxLib_End();
}

//	�X�V
void GameManager::update() {
	DebugDispManager::Instance().Update();
	scenePtr->Update();
}

//	�`��
void GameManager::render() {
	scenePtr->Render();
	DebugDispManager::Instance().Render();
}

//	���s
void GameManager::GameLoop() {
	while (!ProcessMessage()) {
		clsDx();
		ClearDrawScreen();

		fps.Update();
		TimeManager::Instance().Update();
		InputManager::Instance().Update();
		this->update();
		this->render();

		fps.Wait();
#ifdef _DEBUG
		fps.Draw();
#endif // _DEBUG
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE) && CheckHitKey(KEY_INPUT_RETURN))
			return;
	}
}

//	���C��
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	GameManager::Instance().GameLoop();
}