#pragma once
#include <vector>
#include "Vector2D.h"
#include "Component.h"
#include "DrawableComp.h"

class SplitLaser : public Component, public DrawableComp {
public:
	struct LaserBeam
	{
		Vector2Df pos_;			//	座標
		Vector2Df dir_;			//	正規化するベクトル
		double line_time_ = 0;	//	有効時間
		float speed_ = 0;		//	移動速度
		bool canSplit = false;	//	分裂可能か		
	};

public:
	void Start();
	void Update()override;
	void Render()override;


private:
	std::vector<Vector2Df> beams_;	//	レーザー達
	Vector2Df start_pos_;	//	開始座標
	bool active_ = false;	//	有効判定用
};
