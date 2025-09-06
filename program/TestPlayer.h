#pragma once
#include"GameObject.h"

class TestPlayer :public GameObject {
public:
	TestPlayer() = default;
	virtual ~TestPlayer() = default;

	void SetComponents();

	void Update()override;
	void Render()override;
};