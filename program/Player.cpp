#include "Player.h"
#include "RigidbodyComp.h"
#include "ColliderComp.h"
#include "InputMoveComp.h"
#include "GetColor.h"
#include "PlayerState.h"
#include "PlayerStateController.h"
#include "JumpComp.h"
#include "DiveWireController.h"
#include "dive wire.h"
#include "Camera.h"
#include"PlayerRender.h"
#include"sword.h"
#include"ui_health.h"
#include"health.h"
#include"Gun.h"
#include "SwingWire.h"
#include"ColliderEvent.h"
#include"PointSaver.h"


Player::Player() :state(PlayerState::idle)
{
}

/// <summary>
/// 初期化
/// </summary>
Player::Player(int num):state(PlayerState::idle)
{
	auto filePath = posFile + std::to_string(num) + ".txt";
	auto pos = PointSaver::Instance().GetPoints(filePath);
	for (const auto& p : pos) {
		transform.SetPosition(p);
	}

}

/// <summary>
/// コンポーネントの追加
/// </summary>
void Player::SetComponent()
{


	//transform.SetPosition(Vector2D<float>(500, 100));
	auto rigid = AddComponent<RigidbodyComp>();	//	物理
	auto collider = AddComponent<ColliderComp>(Vector2D<float>{ 50, 70 });
	auto input = AddComponent<InputMove>();		//	入力移動
	auto state = AddComponent<PlayerStateComp>(5);
	auto stateCo = AddComponent<StateController>();
	stateCo->Start();
	AddComponent<JumpComp>();	//	ジャンプ処理
	auto diveWire = AddComponent<DiveWire>();
	diveWire->Initialize(collider->size());
	auto diveWirecontro = AddComponent<DiveWireController>();
	diveWirecontro->Initialize(diveWire);
	auto swingWire = AddComponent<SwingWire>();
	swingWire->Start();

	auto anim = AddComponent<PlayerAnim>();
	anim->Initialize(state, input);
	AddComponent<ColliderEvent>();
	//auto health = AddComponent<Health>(1);
	//auto ui_health = AddComponent<UiPlayerHp>();
	//AddComponent<Gun>();
	//ui_health->Set(health);
	//AddComponent<Sword>();
	SetTag(Tag::GetString(TagType::Player));
	SortLayer();	//	layerのソート
}

/// <summary>
/// 各コンポーネントの更新処理
/// </summary>
void Player::Update()
{
	GameObject::Update();
}

void Player::Render()
{
#ifdef _DEBUG
	//	カメラ座標
	Vector2D<float> camera_pos = Camera::Instance().position();
	Vector2D<float> camera_size = Camera::Instance().area_size();

	const auto& trans = transform.WorldPosition();
	const auto& size = GetComponent<ColliderComp>()->size();

	Vector2D<float> draw = trans - camera_pos + (camera_size / 2);

	DrawBoxAA(draw.x, draw.y, draw.x + size.x, draw.y + size.y,
		RED, FALSE);
#endif // _DEBUG

	GameObject::Render();

}

