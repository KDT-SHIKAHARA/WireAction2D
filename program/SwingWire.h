#pragma once
#include"DrawableComp.h"
#include"Component.h"
#include"RigidbodyComp.h"


class SwingWire : public Component, public DrawableComp {

	enum class State { Idle, Firing, Swinging, };


	// 内部処理
	void MoveAnchor();      // アンカー移動
	void CheckAnchorCollision();    // 設置判定
	void CalculateSwing();  // 振り子運動計算
public:
	SwingWire() {};

	//	発射メソッド
	void Start();
	void Fire();			//	ワイヤーの発射
	void Release();			//	ワイヤー解除
	void Update()override;	//	更新
	void Render()override;	//	描画
	bool IsFinish() { return isFinish_; }
private:
	State state_ = State::Idle;
	std::shared_ptr<RigidbodyComp> rigidBody_;
	Vector2Df anchorPos_;
	Vector2Df objPos_;
	Vector2Df size_;
	float wireLength_ = 0.0f;  // アンカーからプレイヤーまでの距離
	
	float initTheta = 0.5f;
	float theta_ = 0.0f;  // 振り子角度
	float omega_ = 0.0f;  // 振り子角速度
	Vector2Df fireDir_;      // 発射方向
	Vector2Df lastVelocity_; // 解除時に保持する速度

	// 定数
	float fireSpeed_ = 2300.0f;    // 発射速度（px/s）
	float maxLength_ = 800.0f;    // ワイヤー最大長
	float gravity_ = 5000.0f;     // 疑似重力
	float damping_ = 0.05f;       // 減衰
	static constexpr float kInputForce = 0.5f;
	bool isFinish_ = false;
};