#include"Needle.h"
#include"ColliderComp.h"
#include"GameObjectMgr.h"
#include"PointSaver.h"
#include"HitBOxRenderComp.h"
#include"tag.h"
#include"DrawGraphComp.h"

//	生成
std::shared_ptr<GameObject> Needle::Create(const Vector2Df& a_position, const Vector2Df& a_size) {
	//	インスタンス生成
	auto needle = std::make_shared<GameObject>();

	//	座標設定
	needle->transform.SetWorldPosition(a_position);

	//	当たり判定
	needle->AddComponent<ColliderComp>(a_size);
	
	//	判定用の四角形描画
	needle->AddComponent<HitBoxRenderComp>();

	//	タグの設定
	needle->SetTag(Tag::GetString(TagType::Needle));

	//	画像読み込み
	needle->AddComponent<DrawGraphComp>(texture);

	//	ゲームオブジェクトの追加
	GameObjMgr::Instance().AddGameObject(needle);

	return needle;
}


//	針のインスタンス全て取得
void Needle::GetNeedle(int num) {
	auto filePath = posFilePath + std::to_string(num) + ".txt";
	auto positions = PointSaver::Instance().GetPoints(filePath);

	for (const auto& pos : positions) {
		Create(pos, Vector2Df{ 32,32 });
	}

}