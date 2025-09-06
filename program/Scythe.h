#pragma once
#include "Component.h"
#include "DrawableComp.h"
#include "vector2d.h"

//	�͈͍U��
class Scythe : public Component, public DrawableComp {
public:
	void Start();
	void Update()override;
	void Render()override;

private:

	const float k_speed_ = 500.f;	//	�b�Ԃ̈ړ����x
	const float k_radius_ = 200.f;	//	�U���͈͂̔��a
	const float k_wait_time_ = 1.f;	//	�U�����L���ɂȂ�܂ł̑ҋ@����
	const float k_attackDuratuin_ = 1.5f;	//	�U�����肪�c�鎞��
	const float  k_stopDistance_ = 80.0f;    // �v���C���[�ɋ߂Â����Ƃ݂Ȃ�����


	double attack_time_ = 0;	//	���ʎ���
	double wait_time_ = 0;	//	�҂�����
	Vector2D<float> target_;	//	�ړ�����W
	Vector2D<float> pos_;	//	�{�X�̍��W�i����p�j

	bool active_ = false;	//	�L��
	bool reachedTarget_ = false;	//	�^�[�Q�b�g�ɓ��B������

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