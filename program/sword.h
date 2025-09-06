#pragma once
#include"Component.h"
#include"DrawableComp.h"
#include<vector>
#include"Circle.h"
#include"vector2d.h"

class Sword : public Component ,public DrawableComp{

	//	“G‚ÌƒŠƒXƒg‚ðŽæ“¾‚µ‚Ä“–‚½‚è”»’è‚ð‚·‚é
	void CheckEnemyHit();


public:

	//	‰ŠúÝ’è
	void Start();

	//	XV•`‰æ
	void Update()override;
	void Render()override;

	//	I—¹ƒƒ\ƒbƒh
	bool isFinish() {
		return attackFrame_ >= kAttackFrame_max_;
	};

private:
	Vector2D<float> gameObj_pos_;
	const double kAttackFrame_max_ = 1.;
	double attackFrame_ = kAttackFrame_max_;
	float radius_ = 50;	//	‰~‚Ì”¼Œa (‚¢‚¢Š´‚¶‚É)
	int	attack_point_ = 5;
};