#pragma once
#include"Component.h"
#include"DrawableComp.h"
#include"vector2d.h"

class Laser : public Component, public DrawableComp {

	//	レーザ内での状態の変化用
	enum class State {
		wait,
		laser,
		finish,
	};

	void start();
public:
	void Update()override;
	void Render()override;

	bool isFinish() {
		return mode_ == State::finish || active_ == false;
	}

private:
	//	サイズと基準座標
	const double k_wait_max_ = 5;
	const double k_frame_max_ = k_wait_max_ * 2;
	static constexpr float mov_speed_ = 5.f;
	Vector2D<float> base_pos_;
	Vector2D<float> screen_pos_;
	Vector2D<float> area_size_;
	Vector2D<float> target_pos_;
	double frame_ = 0;
	State mode_ = State::wait;
	bool active_ = false;



};
