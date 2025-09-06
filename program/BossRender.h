#pragma once
#include "Component.h"
#include "DrawableComp.h"

class BossRenderComp : public Component, public DrawableComp {
public:
	BossRenderComp() {
		layer_ = 0;
	}
	void Update()override {}
	void Render()override;
};
