#pragma once
#include "sceneBase.h"
#include "TextureResource.h"
#include <string>
#include "Particle .h"
#include "BoxButton.h"

class SCTitle : public Scene {

	enum {
		START,
		BOSSDEBUG,
		MAX,
		NONE,
	};

private:

	//	タイトル文字列
	void DrawStr();

	//	メニューの判定処理
	void MenuSelect();

	//	メニューとカーソルがあっていたら何か表示をする
	void MenuDraw();

	//	入力判定
	bool isInput();

public:
	SCTitle();
	void Update()override;
	void Render()override;

private:
	std::shared_ptr<ParticleSystem> particles_;
	std::vector <std::shared_ptr<BoxButton>> menus_;

private:
	std::shared_ptr<TextureResource> bg_;
	std::shared_ptr<TextureResource> str_;
private:
	std::string res_bg_ = "res/Title/bg.jpg";
	std::string res_str_ = "res/Title/str.png";

	int select_num_ = 0;
};