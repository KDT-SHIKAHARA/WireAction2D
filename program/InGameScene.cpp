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


//	������
//	��񏉊������Ȃ����̂�����
InGameScene::InGameScene() {
	stageNumber = 1;
	resetCount = 0;
	bg_filePath_ = "res/map/texture/bg.jpg";
	bg_ = TextureResourceMgr::Instance().GetTexture(bg_filePath_);
	Init();
	grave_ = TextureResourceMgr::Instance().GetTexture("res/icon/grave.png");
}

//	�������ƃC���X�^���X����
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

//	�J�����̍X�V
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

	//	�؂�ւ��������
	if (stageNumber != before_stageNum) {
		//	�ő�l�ɒB���Ă��Ȃ����
		if (stageNumber <= max_stateNum) {
			Init();
		}
		//	�ő�l�ɒB���Ă�����
		else {
			//	���U���g���\�b�h
			Result();
			//	InGame�̒���GameObject�C���X�^���X������������
			//	���U���g�֌W�����Ăяo���`�ɂ���


		}
	}

	//	Result��Ԃ̎�
	if (isResult) {
		//	�X�y�[�X�L�[��
		if (Input::IsKeyOn(KEY_INPUT_SPACE)) {
			//	�^�C�g����ʂɖ߂�
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
	

	std::string text = "���S�񐔁F %d";
	// ������̉������擾
	int textWidth = GetDrawFormatStringWidth(text.c_str());

	// �t�H���g�̍������擾
	int textHeight = GetFontSize();

	// �������W���v�Z
	int x = (WINDOW_W - textWidth) / 2;
	int y = (WINDOW_H - textHeight) / 2;

	// �`��
	SetFontSize(50);
	DrawFormatString(x - 50, y, WHITE, text.c_str(), resetCount);
	SetFontSize(70);

	DxlibRap::TextRenderer::CenterString(WINDOW_W / 2, WINDOW_H / 2 - 150, WHITE, "���U���g");
	SetFontSize(40);
	DxlibRap::TextRenderer::CenterString(WINDOW_W / 2, WINDOW_H / 2 + 150, WHITE, "�X�y�[�X��title�ɖ߂�");
	SetFontSize(16);


}

