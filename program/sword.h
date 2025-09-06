#pragma once
#include"Component.h"
#include"DrawableComp.h"
#include<vector>
#include"Circle.h"
#include"vector2d.h"

class Sword : public Component ,public DrawableComp{

	//	�G�̃��X�g���擾���ē����蔻�������
	void CheckEnemyHit();


public:

	//	�����ݒ�
	void Start();

	//	�X�V�`��
	void Update()override;
	void Render()override;

	//	�I�����\�b�h
	bool isFinish() {
		return attackFrame_ >= kAttackFrame_max_;
	};

private:
	Vector2D<float> gameObj_pos_;
	const double kAttackFrame_max_ = 1.;
	double attackFrame_ = kAttackFrame_max_;
	float radius_ = 50;	//	�~�̔��a (����������)
	int	attack_point_ = 5;
};