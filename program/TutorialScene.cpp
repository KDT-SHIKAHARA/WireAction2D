#include "TutorialScene.h"
#include "GameObjectMgr.h"
#include "Player.h"
#include "debugDef.h"
#include "MapManager.h"
#include "ColliderComp.h"

Tutorial::Tutorial()
{
	auto player = std::make_shared<Player>();
	player->SetComponent();
	player_ = player;
	GameObjMgr::Instance().AddGameObject(player);
	MapManager::Instance().Load(tutorial_map_data_);
}

void Tutorial::Update()
{
	Scene::Update();
	auto pos = player_->transform.WorldPosition() + (player_->GetComponent<ColliderComp>()->size() / 2);
	Camera::Instance().SetFollowPos(pos);
}

void Tutorial::Render()
{
	Scene::Render();
	DEBUG_LOG("Tutorial Scene");
}
