#include "TestPlayer.h"
#include"RigidbodyComp.h"
#include"dxlib.h"
#include"GetColor.h"
#include"input.h"
#include"debugLog.h"
#include"ColliderComp.h"

void TestPlayer::SetComponents(){
	auto rigid =  AddComponent<RigidbodyComp>(1.0f);
	DebugLog::AddDubug("rigid.isGravity", rigid->isGravity_);
	transform.AddDebugLog();
	transform.SetPosition(Vector2D<float>(500, 100));
	AddComponent<ColliderComp>(Vector2D<float>{ 50, 70 });
}

void TestPlayer::Update(){
	GameObject::Update();
	
	//	切り替えできるかデバック用
	if (Input::IsKeyOn(KEY_INPUT_1)) {
		auto input = GetComponent<RigidbodyComp>();
		input->isGravity_.Toggle();
	}
}

void TestPlayer::Render(){
	const auto& pos = transform.WorldPosition();
	const auto& size = GetComponent<ColliderComp>()->size();
	DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, RED, TRUE);
	GameObject::Render();
}
