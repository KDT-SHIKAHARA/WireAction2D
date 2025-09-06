#pragma once
#include"Component.h"
#include"vector2d.h"
#include"flag.h"
#include"Time.h"


class RigidbodyComp :public Component {
	static constexpr float kGravity = 9.8f;

	float mass_;						//	重さ (0なら動かない)
	Vector2D<float> velocity_;		//	移動ベクトル
	Vector2D<float> acceleration_;	//	加速度ベクトル(フレームごとの移動量の加算量)
	Vector2D<float> gravity_;		//	重力（横方向にも対応できるように）
	Vector2D<float> totalForce_;	//	クラス外の移動量の全て(移動、ワイヤーなど)
	float damping_;					//	減衰量
	float friction_ = 10.0f;			//	摩擦
	const float speed_max_ = 1000.0f;
public:
	Flag isGravity_;				//	重力フラグ true: 重力加算 false: 無重力
	Flag isGrounded_;				//	地面に設置判定　true: 設置している	false:設置してない
	Flag isStatic_;					//	物理挙動を行うかどうか true: 行わない false: 行う

	RigidbodyComp(float arg_mass = 1.0f, Flag arg_isGravity = true, Flag arg_isStatic = false);
	virtual ~RigidbodyComp() = default;

	//	外力の加算
	void AddForce(const Vector2D<float>& arg_force);

	//	移動ベクトル追加
	void AddVelocity(const Vector2D<float>& arg_velocity);

	//	移動ベクトルセット
	void SetVelocity(const Vector2D<float>&arg_velocity);

	//	移動ベクトルの取得
	Vector2D<float> velocity()const { return velocity_ * Time::deltaTime(); }
	Vector2Df velocityRaw()const { return velocity_; }

	//	更新
	void Update()override;


}; // class

