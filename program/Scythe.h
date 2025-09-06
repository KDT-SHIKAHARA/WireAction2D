#pragma once
#include "Component.h"
#include "DrawableComp.h"
#include "vector2d.h"

//	範囲攻撃
class Scythe : public Component, public DrawableComp {
public:
	void Start();
	void Update()override;
	void Render()override;

private:

	const float k_speed_ = 500.f;	//	秒間の移動速度
	const float k_radius_ = 200.f;	//	攻撃範囲の半径
	const float k_wait_time_ = 1.f;	//	攻撃が有効になるまでの待機時間
	const float k_attackDuratuin_ = 1.5f;	//	攻撃判定が残る時間
	const float  k_stopDistance_ = 80.0f;    // プレイヤーに近づいたとみなす距離


	double attack_time_ = 0;	//	効果時間
	double wait_time_ = 0;	//	待ち時間
	Vector2D<float> target_;	//	移動先座標
	Vector2D<float> pos_;	//	ボスの座標（判定用）

	bool active_ = false;	//	有効
	bool reachedTarget_ = false;	//	ターゲットに到達したか

};




//class SkillBase {
//public:
//	virtual void Start() {
//		if (!active_)return;
//		active_ = true;
//	}
//	virtual void Update() = 0;
//	virtual void Render() = 0;
//protected:
//	bool active_ = false;
//};
//
//
//class meteor : public SkillBase {
//
//public:
//	void Update()override{
//		if (!active_)return;
//	}
//
//	void Render()override {
//
//	}
//
//};
//
//
//#include<vector>
//
//
//class Base {
//private:
//	std::vector< std::shared_ptr<SkillBase>>skill_;
//
//
//public:
//
//	Base() {
//		skill_.push_back(std::make_shared<meteor>());
//	}
//
//	void Skill(int num) {
//		skill_[num]->Start();
//	}
//
//	void Update() {
//		for (const auto& skill : skill_) {
//			skill->Update();
//		}
//	}
//
//};