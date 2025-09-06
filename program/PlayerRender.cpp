#include "PlayerRender.h"
#include "GameObject.h"
#include "ColliderComp.h"
#include "Camera.h"
#include"PlayerState.h"
#include"InputMoveComp.h"


PlayerAnim::PlayerAnim()
{

	//	描画率
	const float exRate = 1.5f;
	//	
	const std::string& base_str = "res/player/texture/";
	const std::string& Idle_str = "idle/Unitychan_Idle_";
	const std::string& move_str = "run/Unitychan_Run_";
	const std::string& jump_up_str = "jump/up/Unitychan_Jump_Up_";
	const std::string& jump_fall_str = "jump/fall/Unitychan_Jump_Fall_";
	const std::string& sword = "attack/Unitychan_Soard_Combo_";
	//	アニメーションクラスのインスタンスも同時に作ってね
	animations_[AnimType::Idle].LoadFrames(base_str  + Idle_str, 3,0.4f, exRate);
	animations_[AnimType::Run].LoadFrames(base_str + move_str, 18, 0.1f, exRate);
	animations_[AnimType::Jump_up].LoadFrames(base_str + jump_up_str, 2, 0.4, exRate);
	animations_[AnimType::Jump_fall].LoadFrames(base_str + jump_fall_str, 2, 0.4, exRate);
	animations_[AnimType::Attack].LoadFrames(base_str + sword, 9, 0.08, exRate + 0.5,Anim2D::PlayMode::Ones);
}

void PlayerAnim::Update()
{
	if (!state_) return;
	auto rigid = GetGameObj()->GetComponent<RigidbodyComp>();
	if (!rigid) return;

	//	前の状態を記録
	AnimType before_anim = now_type_;


	//	ここスイッチ文ね state_->GetStateを見てね
	//	stateコンポーネントのenum classを見て
	//	animtypeの数値を設定する
	switch (state_->GetState()) {
	case _P_STATE::Idle:
		now_type_ = AnimType::Idle; 
		break;
	case _P_STATE::Move:
		now_type_ = AnimType::Run;
		break;
	case _P_STATE::Jump:
		//	移動量を見て上方向か下方向かをみてanimationを変える
		if (!rigid) return;

		//	移動量によってUp,Fallを変える
		if (rigid->velocity().y <  0.0f) {
			now_type_ = AnimType::Jump_up;
		}
		else if(rigid->velocity().y > 0.0f) {
			now_type_ = AnimType::Jump_fall;
		}
		break;
	case _P_STATE::Attack:
		now_type_ = AnimType::Attack;
		break;
	}

	//	落下アニメーションを行うかどうか
	if (checkFallAnimType()) {
		if (checkFall(rigid)) {
			now_type_ = AnimType::Jump_fall;

		}
	}

	//	今の状態と前の状態が変わっていたら前の状態のリセットを行う
	if (before_anim != now_type_) {
		animations_[before_anim].Reset();
	}

	//	animtypeをインデックスに持つ更新メソッドを呼び出す。
	animations_[now_type_].Update();
	if (!input_) return;
	animations_[now_type_].isFlip_.Set(input_->isReverse);

}

void PlayerAnim::Render()
{

	//	カメラ座標
	Vector2D<float> camera_pos = Camera::Instance().position();
	Vector2D<float> camera_size = Camera::Instance().area_size();

	const auto& trans = GetGameObj()->transform.WorldPosition();
	const auto& size = GetGameObj()->GetComponent<ColliderComp>()->size();

	Vector2D<float> draw = trans - camera_pos + (camera_size / 2);
	if (now_type_ == AnimType::Attack) draw.y -= 15;
	animations_[now_type_].Render(draw.x + size.x / 2, draw.y + size.y / 2 - 10);
}
