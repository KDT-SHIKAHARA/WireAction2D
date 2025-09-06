#pragma once

#include"Component.h"
#include"DrawableComp.h"
#include"flag.h"
#include"vector2d.h"

/// <summary>
/// ダイブワイヤーの管理
/// </summary>
class DiveWire : public Component, public DrawableComp {



public:
	DiveWire();
	virtual ~DiveWire() = default;

	void Initialize(const Vector2D<float> size) {
		size_ = size;
	}

	void Update()override;
	void Render()override;
	
	void Start();
	bool IsFinished()const;

	//	リセット
	void ReSet() {
		isAnchored = false;
		isFinished_ = false;
		chargeFrame_ = 0.0f;
	}

	Vector2D<float> anchorPos()const { return anchorPos_; };

	Flag isAnchored = false;	//	アンカーが固定されているかどうかの判定
private:

	Vector2D<float> gameObjPos_;
	Vector2D<float> anchorPos_;
	Vector2D<float> velocity_;
	Vector2D<float> size_;
	double chargeFrame_ = 0;
	static constexpr double kChargeFrameMax_ = 0.1;	//	発射するまでのcharge時間
	float length_ = 0;
	static constexpr float kAnchorSpeed_ = 3500.0f;	//	アンカーの移動速度
	static constexpr float kGameObjectSpeed_ = 2000.0f;	//	移動速度
	static constexpr float kWireLength_ = 600.0f;	//	ワイヤーの最大の長さ
	static constexpr int cir_max_ = 10;	//	アンカー発射までのチャージ中の弾の最大数
	static constexpr float cir_one_frame = kChargeFrameMax_ / cir_max_;	//	弾の時間
	static constexpr float cir_distance = 100;

	Flag isFinished_ = false;
};


