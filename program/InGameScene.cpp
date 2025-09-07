#include"InGameScene.h"
#include"MapManager.h"
#include"GameObjectMgr.h"
#include"debugDef.h"
#include"Needle.h"
#include"ColliderEvent.h"
#include"TextureResourceMng.h"
#include"Goal.h"
#include"SystemConfig.h"
#include"GetColor.h"
#include"input.h"
#include"GameManager.h"
#include"Title.h"
#include"DrawRap.h"


//	初期化
//	一回初期化しないものもここ
InGameScene::InGameScene() {
	stageNumber = 1;
	resetCount = 0;
	bg_filePath_ = "res/map/texture/bg.jpg";
	bg_ = TextureResourceMgr::Instance().GetTexture(bg_filePath_);
	Init();
	grave_ = TextureResourceMgr::Instance().GetTexture("res/icon/grave.png");
}

//	初期化とインスタンス生成
void InGameScene::Init() {
	mapDataFile = "res/map/data/stage/" + std::to_string(stageNumber) + ".txt";
	MapManager::Instance().Load(mapDataFile);
	GameObjMgr::Instance().AllDestroyedGameObjects();
	auto player = std::make_shared<Player>(stageNumber);
	player->SetComponent();
	player_ = player;
	GameObjMgr::Instance().AddGameObject(player);
	Needle::GetNeedle(stageNumber);
	goal_ = Goal::Create(stageNumber);
	GameObjMgr::Instance().AddGameObject(goal_);

}

//	カメラの更新
void InGameScene::Update() {
	Scene::Update();
	auto pos = player_->transform.WorldPosition() + (player_->GetComponent<ColliderComp>()->size() / 2);
	Camera::Instance().SetFollowPos(pos);

	auto before_stageNum = stageNumber;

	auto end = player_->GetComponent<ColliderEvent>();
	if (end) {
		if (end->hitDeadly) {
			Init();
			resetCount++;
		}
	}
	auto next = goal_->GetComponent<ColliderEvent>();
	if (next) {
		if (next->hitDeadly) {
			stageNumber++;
		}

	}

	//	切り替わった時に
	if (stageNumber != before_stageNum) {
		//	最大値に達していなければ
		if (stageNumber <= max_stateNum) {
			Init();
		}
		//	最大値に達していたら
		else {
			//	リザルトメソッド
			Result();
			//	InGameの中のGameObjectインスタンスを初期化して
			//	リザルト関係だけ呼び出す形にする


		}
	}

	//	Result状態の時
	if (isResult) {
		//	スペースキーで
		if (Input::IsKeyOn(KEY_INPUT_SPACE)) {
			//	タイトル画面に戻る
			GameManager::Instance().CreateScene<SCTitle>();
		}
	}

}

void InGameScene::Render() {
	DrawGraph(0, 0, bg_->GetHandle(), TRUE);
	DrawRotaGraph(100, WINDOW_H - 100, 1.0f, 0.0f, grave_->GetHandle(), TRUE);
	SetFontSize(100);
	DrawFormatString(80, WINDOW_H - 150, BLACK, "%d", resetCount);
	SetFontSize(16);
	Scene::Render();
	ResultRender();
	DEBUG_LOG("InGame Scene");

}


void InGameScene::ResetStage() {

}

void InGameScene::NextStage() {

}

void InGameScene::Result()
{
	isResult = true;
	GameObjMgr::Instance().AllDestroyedGameObjects();
}

void InGameScene::ResultRender()
{
	if (!isResult) return;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	

	std::string text = "死亡回数： %d";
	// 文字列の横幅を取得
	int textWidth = GetDrawFormatStringWidth(text.c_str());

	// フォントの高さを取得
	int textHeight = GetFontSize();

	// 中央座標を計算
	int x = (WINDOW_W - textWidth) / 2;
	int y = (WINDOW_H - textHeight) / 2;

	// 描画
	SetFontSize(50);
	DrawFormatString(x - 50, y, WHITE, text.c_str(), resetCount);
	SetFontSize(70);

	DxlibRap::TextRenderer::CenterString(WINDOW_W / 2, WINDOW_H / 2 - 150, WHITE, "リザルト");
	SetFontSize(40);
	DxlibRap::TextRenderer::CenterString(WINDOW_W / 2, WINDOW_H / 2 + 150, WHITE, "スペースでtitleに戻る");
	SetFontSize(16);


}

