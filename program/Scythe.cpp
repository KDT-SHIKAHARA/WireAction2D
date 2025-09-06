#include<cmath>
#include "Scythe.h"
#include "Time.h"
#include "GameObjectMgr.h"
#include "GameObject.h"
#include "input.h"
#include "Camera.h"

void Scythe::Start() 
{
	active_ = true;
	reachedTarget_ = false;
	attack_time_ = 0;
	wait_time_ = 0;
	pos_ = GetGameObj()->transform.WorldPosition();
	auto targets = GameObjMgr::Instance().GetGameObjWithTag(Tag::GetString(TagType::Player));
	for (const auto& player : targets) {
		target_ = player->transform.WorldPosition();
	}
}


void Scythe::Update()
{

#ifdef _DEBUG
	if(Input::IsKeyOn(KEY_INPUT_Y)){
		Start();
	}
#endif // _DEBUG


	if (!active_)return;


	//	デルタタイム取得
	auto dt = Time::deltaTime();

	//	攻撃を無効 なら
	if (!reachedTarget_) {
		//	移動ベクトルを取得して
		auto dir = target_ - pos_;
		//	長さを取得
		auto len = dir.GetLength();

		//	距離がまだ遠かったら
		if (len > k_stopDistance_) {

			GetGameObj()->transform.MoveToTarget(target_,(float)(k_speed_ * dt));
			pos_ = GetGameObj()->transform.WorldPosition();

			////	正規化
			//dir.Normalize();

			////	移動
			//pos_ += dir * (float)(k_speed_ * dt);

		}
		//	プレイヤーの近くなら
		else {
			//	フラグを立て
			reachedTarget_ = true;

			//	溜め時間セット
			wait_time_ = k_wait_time_;
		}

		////	座標更新
		//GetGameObj()->transform.SetWorldPosition(pos_);

	}
	//	有効状態で溜め状態なら
	else if (wait_time_ > 0.0) {
		//	溜め時間を減らして
		wait_time_ -= dt;

		//	待ち時間が終了していたら
		if (wait_time_ <= 0.0) {
			//	攻撃時間セット
			attack_time_ = k_attackDuratuin_;
		}
	}
	//	有効状態で攻撃状態なら
	else if (attack_time_ > 0.0) {
		//	攻撃時間を減らして
		attack_time_ -= dt;

		//	攻撃時間が終了していたら
		if (attack_time_ <= 0.0) {
			//	有効フラグを折る
			active_ = false;
		}
	}
}

void Scythe::Render()
{
	if (!active_) return;

	// カメラ位置（例：カメラがワールドのどこを見ているか）
	Vector2D<float> camPos = Camera::Instance().position();
	Vector2D<float> camOffset = Camera::Instance().area_size();

	// ワールド座標 → スクリーン座標
	Vector2D<float> screenPos = pos_ - camPos + camOffset / 2;

	if (attack_time_ > 0.0) {
		// --- 攻撃範囲（赤い円） ---
		DrawCircle((int)screenPos.x, (int)screenPos.y, (int)k_radius_, GetColor(255, 0, 0), TRUE);
	}
	else if (reachedTarget_ && wait_time_ > 0.0) {
		// --- 溜め演出（光が収束していく） ---
		double t = 1.0 - (wait_time_ / k_wait_time_);
		int radius = (int)(k_radius_ * (1.0 - t * 0.7));
		int alpha = (int)(128 + 127 * t);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawCircle((int)screenPos.x, (int)screenPos.y, radius, GetColor(255, 200, 100), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 外側に光のリング
		DrawCircle((int)screenPos.x, (int)screenPos.y, radius + 10, GetColor(255, 255, 200), FALSE);
	}
	else {
		// --- 移動中のボス（灰色の円で描画） ---
		DrawCircle((int)screenPos.x, (int)screenPos.y, 16, GetColor(200, 200, 200), TRUE);
	}
}

