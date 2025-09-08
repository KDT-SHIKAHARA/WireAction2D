#include "explanation.h"
#include "TextureResourceMng.h"
#include "input.h"
#include "GameManager.h"
#include "InGameScene.h"
#include "DrawRap.h"
#include "SystemConfig.h"
#include "GetColor.h"
#include "Time.h"
Exp::Exp()
{
	std::string texFile = "res/exp/sousa.png";
	texture_ = TextureResourceMgr::Instance().GetTexture(texFile);
}

void Exp::Update()
{
	if (Input::IsMouseOn(MOUSE_INPUT_LEFT)) {
		GameManager::Instance().CreateScene<InGameScene>();
	}
}

void Exp::Render()
{
	DrawGraph(0, 0, texture_->GetHandle(), TRUE);
	frame += Time::deltaTime();
	if (frame > 1.0) frame = 0;

	if (frame < 0.5) {
		auto posX = WINDOW_W / 2;
		auto posY = WINDOW_H / 2 + 100;

		SetFontSize(70);
		DxlibRap::TextRenderer::CenterString(posX, posY, WHITE, "START Click ");
		SetFontSize(16);

	}
}
