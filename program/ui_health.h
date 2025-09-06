#pragma once
#include<vector>
#include"Component.h"
#include"DrawableComp.h"
#include"SystemConfig.h"


class Health;
class UiPlayerHp : public Component, public DrawableComp {

	void Box(int num);

public:
	UiPlayerHp() {
		layer_ = 1;
	}

	//	必要な情報セット
	//	実行順が大切なのでコンストラクタにはしません。（大事）
	void Set(std::shared_ptr<Health> healsh) {
		healsh_ = healsh;
	}

	void Update()override;
	void Render()override;

private:
	std::shared_ptr<Health> healsh_;	//	体力クラスのポインタ
	int hp_ = 0;

	//	定数
	const float base_pos_x_ = 100;
	const float base_pos_y_ = WINDOW_H - 60;
	const float base_size_x_ = 200;
	const float base_size_y_ = 40;
	const float size_x_ = 20;
	const float size_y_ = 40;

	const int gapX_ = 10;     // 横方向の隙間
	const int gapY_ = 5;     // 横方向の隙間

};