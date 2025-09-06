#include "BossScene.h"
#include "debugDef.h"
#include "Player.h"
#include "GameObjectMgr.h"
#include "ColliderComp.h"
#include "Boss.h"


BossStage::BossStage()
{
	auto player = std::make_shared<Player>();
	player->SetComponent();
	player_ = player;
	GameObjMgr::Instance().AddGameObject(player);
	MapManager::Instance().Load(boss_map_data_);
	GameObjMgr::Instance().AddGameObject(Boss::GetGameObj());
}

void BossStage::Update()
{
	Scene::Update();
	auto pos = player_->transform.WorldPosition() + (player_->GetComponent<ColliderComp>()->size() / 2);
	Camera::Instance().SetFollowPos(pos);
}

void BossStage::Render()
{
	Scene::Render();
}
