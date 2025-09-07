#pragma once
#include"Component.h"

class ColliderEvent : public Component {
public:
	bool hitDeadly = false;
	void Update()override{}
};

