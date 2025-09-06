#pragma once

#include"Component.h"
#include"DrawableComp.h"
#include"flag.h"
#include"vector2d.h"

/// <summary>
/// �_�C�u���C���[�̊Ǘ�
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

	//	���Z�b�g
	void ReSet() {
		isAnchored = false;
		isFinished_ = false;
		chargeFrame_ = 0.0f;
	}

	Vector2D<float> anchorPos()const { return anchorPos_; };

	Flag isAnchored = false;	//	�A���J�[���Œ肳��Ă��邩�ǂ����̔���
private:

	Vector2D<float> gameObjPos_;
	Vector2D<float> anchorPos_;
	Vector2D<float> velocity_;
	Vector2D<float> size_;
	double chargeFrame_ = 0;
	static constexpr double kChargeFrameMax_ = 0.1;	//	���˂���܂ł�charge����
	float length_ = 0;
	static constexpr float kAnchorSpeed_ = 3500.0f;	//	�A���J�[�̈ړ����x
	static constexpr float kGameObjectSpeed_ = 2000.0f;	//	�ړ����x
	static constexpr float kWireLength_ = 600.0f;	//	���C���[�̍ő�̒���
	static constexpr int cir_max_ = 10;	//	�A���J�[���˂܂ł̃`���[�W���̒e�̍ő吔
	static constexpr float cir_one_frame = kChargeFrameMax_ / cir_max_;	//	�e�̎���
	static constexpr float cir_distance = 100;

	Flag isFinished_ = false;
};


