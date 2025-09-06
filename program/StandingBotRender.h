#pragma once
#include<string>
#include"Component.h"
#include"DrawableComp.h"
#include"TextureResource.h"

class StandBotRender :public Component, public DrawableComp {
public:
	StandBotRender();
	void Update()override {}
	void Render()override;

private:
	std::shared_ptr<TextureResource> res_texture_;
	std::string res_tex_filePath_ = "";

};