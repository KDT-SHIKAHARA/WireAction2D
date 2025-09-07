#pragma once
#include"GameObject.h"
#include<memory>
#include<string>
#include<vector>

class Needle {
	inline static std::string posFilePath = "res/needle/pos";
	inline static std::string texture = "res/needle/texture.png";
public:

	Needle() = default;
	virtual ~Needle() = default;
	static std::shared_ptr<GameObject> Create(const Vector2Df& a_position, const Vector2Df& a_size);
	static void GetNeedle(int num);
};
