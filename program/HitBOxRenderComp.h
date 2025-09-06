#pragma once
#include "Component.h"
#include "DrawableComp.h"

class HitBoxRenderComp : public Component, public DrawableComp {
public:
	HitBoxRenderComp(int num = 0) {
		layer_ = num;
	}
	void Update()override {}
	void Render()override;
};
