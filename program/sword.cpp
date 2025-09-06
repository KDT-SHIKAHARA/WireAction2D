#include "sword.h"
#include "GameObject.h"
#include "RigidbodyComp.h"
#include "Time.h"
#include "dxlib.h"
#include "ColliderComp.h"
#include "GetColor.h"
#include "PlayerStateController.h"
#include "Camera.h"
#include "GameObjectMgr.h"
#include "tag.h"
#include "Hit.h"
#include "health.h"


/// <summary>
/// GameObjectManagerから指定したタグのリストを作成して
/// そのリストと当たり判定をする
/// </summary>
void Sword::CheckEnemyHit()
{
	auto enemy_list = GameObjMgr::Instance().GetGameObjWithTag(Tag::GetString(TagType::Enemy));

	//	座標から範囲判定
	for (auto enemy : enemy_list){
		//	当たり判定用のコンポーネントの確認
		auto colldier = enemy->GetComponent<ColliderComp>();
		if (!colldier) continue;
		auto size = colldier->size();

		//	円と四角形の当たり判定
		if (Hit::CheckCircleRect(enemy->transform.WorldPosition(), size,
			gameObj_pos_, radius_)) {

			//	体力コンポーネントを作って、生存の管理コンポーネントを作成。
			auto healsh = enemy->GetComponent<Health>();
			if (!healsh) return;
			healsh->Damage(attack_point_);
		}
	}
}

//	開始
void Sword::Start() {
	//auto direction = GetGameObj()->transform.GetAngleType();
	//switch (direction) {
	//case Direction::Right:
	//	angle_ = 45.f;	//	開始角度
	//	angleIncrement_ = -90.f;	//	
	//	break;
	//case Direction::Left:
	//	angle_ = 135.f;
	//	angleIncrement_ = 90.f;
	//	break;
	//case Direction::Up:
	//	angle_ = 60.f;
	//	angleIncrement_ = 70.0f;
	//	break;
	//case Direction::Down:
	//	angle_ = 270.f;
	//	angleIncrement_ = -70.0f;
	//	break;
	//}

	//	当たり判定をする時間のリセット
	attackFrame_ = 0;

}


void Sword::Update()
{

	//	入力判定
	auto stateCom = GetGameObj()->GetComponent<StateController>();
	if (!stateCom)return;
	//	入力を行えるかどうかを判定する
	if (stateCom->CanAttack()) {
		//	入力判定
		if (Input::IsMouseOn(MOUSE_INPUT_LEFT)) {
			Start();
			//	状態の変更
			stateCom->RequestAttack();
		}
	};


	//	行うかどうかを判定する
	if (attackFrame_ >= kAttackFrame_max_) return;

	auto size = GetGameObj()->GetComponent<ColliderComp>()->size();
	//	ゲームオブジェクトの座標設定
	gameObj_pos_ = GetGameObj()->transform.WorldPosition() + size / 2;

	//	時間経過
	attackFrame_ += Time::deltaTime();

	//	敵と当たり判定をする



}

void Sword::Render()
{
	if (isFinish())return;

#ifdef _DEBUG
	auto draw = gameObj_pos_ - Camera::Instance().position() + (Camera::Instance().area_size() / 2);
	DrawCircleAA(draw.x, draw.y, radius_, 10, RED, FALSE,3.0f);
#endif // _DEBUG

}
