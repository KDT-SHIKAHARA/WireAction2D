#pragma once
#include"sceneBase.h"
#include"TextureResource.h"

#include<memory>
#include<string>

class Exp : public Scene {
public:
	Exp();
	void Update()override;
	void Render()override;
private:
	std::shared_ptr<TextureResource> texture_;
	float frame = 0;
};