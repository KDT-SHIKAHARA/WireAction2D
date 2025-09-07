#include"Goal.h"
#include"PointSaver.h"
#include"ColliderComp.h"
#include"ColliderEvent.h"
#include"HitBOxRenderComp.h"
#include"tag.h"
#include"DrawGraphComp.h"

std::shared_ptr<GameObject> Goal::Create(int num) {
	//	インスタンス
	auto goal = std::make_shared<GameObject>();


	auto filePath = posFile + std::to_string(num) + ".txt";

	//	座標
	auto pos = PointSaver::Instance().GetPoints(filePath);

	for (const auto& p : pos) {
		goal->transform.SetWorldPosition(p);
	}

	//	当たり判定用
	goal->AddComponent<HitBoxRenderComp>();

	Vector2Df size = { 32,32 };

	//	当たり判定
	auto collider = goal->AddComponent<ColliderComp>(size);
	collider->isPush.Set(false);

	//	イベント通知
	goal->AddComponent<ColliderEvent>();

	//	画像
	goal->AddComponent<DrawGraphComp>(texture);

	//	タグの設定
	goal->SetTag(Tag::GetString(TagType::Goal));



	return goal;
}