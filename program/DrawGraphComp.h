#pragma once
#include"DrawableComp.h"
#include"Component.h"
#include"TextureResource.h"

#include<string>

class DrawGraphComp : public Component, public DrawableComp {
public:
	DrawGraphComp(const std::string& filePath);
	void Update()override {};
	void Render()override;

private:
	std::shared_ptr<TextureResource> texture_;
};