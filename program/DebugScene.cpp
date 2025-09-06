#include "DebugScene.h"
#include "debugDef.h"
#include "DebugLog.h"
#include "Player.h"
#include "GameObjectMgr.h"
#include "ColliderComp.h"
#include "Boss.h"

SceneDebug::SceneDebug(){
	auto player = std::make_shared<Player>();
	player->SetComponent();
	player_ = player;
	GameObjMgr::Instance().AddGameObject(player);
	MapManager::Instance().Load(boss_map_data_);
	GameObjMgr::Instance().AddGameObject(Boss::GetGameObj());

}

void SceneDebug::Update(){
	Scene::Update();
	auto pos = player_->transform.WorldPosition() + (player_->GetComponent<ColliderComp>()->size() / 2);

	Camera::Instance().SetFollowPos(pos);
	// Camera::Instance().SetFollowPos(player_->transform.WorldPosition());*/
}

void SceneDebug::Render()
{
	Scene::Render();
	DEBUG_LOG("debug scene");
	auto pos = player_->transform.WorldPosition();
	DebugLog::Log("player_x:", pos.x, 0, 40);
	DebugLog::Log("player_y:", pos.y, 0, 60);

}
