#pragma once
#include<unordered_map>

#include"Anim2D.h"
#include"DrawableComp.h"
#include"RigidbodyComp.h"
#include"PlayerState.h"


class InputMove;
/// <summary>
/// PlayerStateCompの内部数値を見て
/// </summary>
class PlayerAnim : public Component, public DrawableComp {

	enum class AnimType {
		Idle,
		Run,
		Jump_up,
		Jump_fall,
		Wire,
		Attack,
		Extra,
		Damage,
		Dead,
	};

	//	落ちているか判定
	bool checkFall(const std::shared_ptr<RigidbodyComp>& rigid_ptr) {
		if (!rigid_ptr->isGrounded_)fallFrame++;
		else fallFrame = 0;
		return fallFrame > 10;
	}

	//	落ちるアニメーションを行う状態か
	bool checkFallAnimType() {
		return now_type_ == AnimType::Idle
			|| now_type_ == AnimType::Run;
			
	}

public:
	void Initialize(std::shared_ptr<PlayerStateComp> state, std::shared_ptr<InputMove> input) {
		state_ = state;
		input_ = input;
	}

	PlayerAnim();
	virtual ~PlayerAnim() = default;

	void Update()override;
	void Render()override;

private:
	std::shared_ptr<InputMove> input_;
	std::shared_ptr<PlayerStateComp> state_;
	std::unordered_map<AnimType, Anim2D> animations_;
	AnimType now_type_ = AnimType::Idle;
	int fallFrame = 0;
};
