#pragma once
#include <vector>
#include "Vector2D.h"
#include "Component.h"
#include "DrawableComp.h"

class SplitLaser : public Component, public DrawableComp {
public:
	struct LaserBeam
	{
		Vector2Df pos_;			//	���W
		Vector2Df dir_;			//	���K������x�N�g��
		double line_time_ = 0;	//	�L������
		float speed_ = 0;		//	�ړ����x
		bool canSplit = false;	//	����\��		
	};

public:
	void Start();
	void Update()override;
	void Render()override;


private:
	std::vector<Vector2Df> beams_;	//	���[�U�[�B
	Vector2Df start_pos_;	//	�J�n���W
	bool active_ = false;	//	�L������p
};
