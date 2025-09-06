#include "StandingBotRender.h"
#include "TextureResourceMng.h"
#include "Camera.h"
#include"GameObject.h"
#include "ColliderComp.h"
#include"GetColor.h"

StandBotRender::StandBotRender(){
	res_texture_ = TextureResourceMgr::Instance().GetTexture(res_tex_filePath_);
	
}

void StandBotRender::Render()
{
	//	取得
	auto camera_pos = Camera::Instance().position();
	auto camera_size = Camera::Instance().area_size();
	//	座標
	const auto& trans = GetGameObj()->transform.WorldPosition();
	//	サイズ
	const auto& size = GetGameObj()->GetComponent<ColliderComp>()->size();
	Vector2D<float> draw = trans - camera_pos + (camera_size / 2);
	DrawBoxAA(draw.x, draw.y, draw.x + size.x, draw.y + size.y,
		RED, FALSE);

}
