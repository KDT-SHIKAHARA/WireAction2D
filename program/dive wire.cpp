#include "dive wire.h"
#include "MapManager.h"
#include "input.h"
#include "GameObject.h"
#include "PlayerStateController.h"
#include "Time.h"
#include "dxlib.h"
#include "GetColor.h"
#include "ColliderComp.h"
#include "RigidbodyComp.h"
#include "Camera.h"

DiveWire::DiveWire()
{
}

void DiveWire::Update()
{
	//	停止して、移動などもできない状態で設置判定まで行うので
	// 座標の更新は一旦なくす

	
	////	座標の取得
	//gameObjPos_ = GetGameObj()->transform.WorldPosition();

	//	今の状態を見る
	auto state = GetGameObj()->GetComponent<PlayerStateComp>();
	auto rigid = GetGameObj()->GetComponent<RigidbodyComp>();

	if (!state || !rigid)return;
	if (state->GetState() != _P_STATE::dive) return;

	//	ワイヤーの中断処理
	if (Input::IsKeyOn(KEY_INPUT_SPACE)) {
		isFinished_ = true;
	}

	//	アンカー発射までの待ち時間
	if (chargeFrame_ < kChargeFrameMax_) {
		chargeFrame_ += Time::deltaTime();
		return;
	}


	//	アンカーが設置されていなかったら移動処理をする
	if (!isAnchored) {
		//	正規化した移動ベクトル * 移動速度(1秒間の移動速度 * 1Fの時間)
		anchorPos_ += (velocity_ * kAnchorSpeed_) * Time::deltaTime();
		

		//	長さの取得
		length_ = Get2Distance<float>(anchorPos_, gameObjPos_);

		//	設置判定をする
		if (MapManager::Instance().CheckPointHit(anchorPos_)) {
			isAnchored = true;
		}
		//	設置されていなくて、長さが最大を越していたら処理を終了する
		else if (length_ >= kWireLength_) {
			isFinished_ = true;
		}
	}
	//	アンカーが設置されていたら
	else {

		////	判定フラグを確認 true: 終了
		//if (isFinished_) {
		//	return;
		//}


		

		//	現在の座標取得
		gameObjPos_ = (GetGameObj()->transform.WorldPosition() + (size_ / 2));

		//	移動ベクトルの計算
		Vector2D<float> tmp_velocity = anchorPos_ - gameObjPos_;

		//	正規化
		tmp_velocity.Normalize();

		//	二点間の距離と長さの計算
		float length = Get2Distance(anchorPos_, gameObjPos_);

		//	移動する実際の距離
		float gameObjSpeed = kGameObjectSpeed_;

		//	移動する距離とアンカーと座標の距離の計算
		tmp_velocity = tmp_velocity * gameObjSpeed;

		//	移動量セット
		rigid->SetVelocity(tmp_velocity);

		//	ワイヤー状態を解除するかどうかの判定
		if (MapManager::Instance().CheckAABB(GetGameObj())) {
			isFinished_ = true;
			rigid->SetVelocity({ 0,0 });
		}

	}
}

void DiveWire::Render()
{

	auto state = GetGameObj()->GetComponent<PlayerStateComp>();
	if (!state)return;
	if (state->GetState() != _P_STATE::dive) return;

	const auto& camera_pos = Camera::Instance().position();
	const auto& camera_size = Camera::Instance().area_size();

	float screen_gameObjX = gameObjPos_.x - camera_pos.x + camera_size.x / 2;
	float screen_gameObjY = gameObjPos_.y - camera_pos.y + camera_size.y / 2;
	float screen_anchorX = anchorPos_.x - camera_pos.x + camera_size.x / 2;
	float screen_anchorY = anchorPos_.y - camera_pos.y + camera_size.y / 2;

	DrawLineAA(screen_gameObjX, screen_gameObjY, screen_anchorX, screen_anchorY,
		SKYBLUE);

	//	アンカー発射までの時間の時だけ
	if (chargeFrame_ < kChargeFrameMax_) {
		
		//	周りに浮いている型の数を計算
		int cir_num = static_cast<int>(chargeFrame_ / (cir_one_frame));

		//	チャージ中の弾を描画
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		for (int i = 0; i <= cir_num; i++) {
			//	float angleDeg = (360.0f / cir_num) * i; 
			//	のcir_num にすれば動作するたびに１つ当たりの角度が変化しないので
			//	治りますが、見た目的にこっちのほうがかっこいいのでこれにします。
			//	by 2025.8.11に自分より

			float angleDeg = (360.0f / cir_num) * i;
			//float angleDeg = (360.0f / cir_max_) * i;
			Vector2D<float> pos = GetPointFromAngle(gameObjPos_, cir_distance, angleDeg);
			
			// posもスクリーン座標に変換
			float screen_posX = pos.x - camera_pos.x + camera_size.x / 2;
			float screen_posY = pos.y - camera_pos.y + camera_size.y / 2;


			DrawCircle(screen_posX, screen_posY, 5, BLUE, SKYBLUE);
			
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

/// <summary>
/// 移動ベクトルの計算
/// </summary>
void DiveWire::Start() {
	//auto size = GetGameObj()->GetComponent<ColliderComp>()->size();
	anchorPos_ = gameObjPos_ = (GetGameObj()->transform.WorldPosition() + (size_ / 2));
	Vector2D<float> mosue = { (float)Input::MouseX(),(float)Input::MouseY() };
	const Vector2D<float>& camera_pos = Camera::Instance().position();
	const Vector2D<float>& camera_size = Camera::Instance().area_size();
	Vector2D<float> world_mouse = camera_pos - camera_size / 2.f + mosue;
	velocity_ = world_mouse - gameObjPos_;
	velocity_.Normalize();
}


bool DiveWire::IsFinished() const
{
	return isFinished_;
}
