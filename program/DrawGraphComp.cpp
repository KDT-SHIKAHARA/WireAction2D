#include "DrawGraphComp.h"
#include"TextureResourceMng.h"
#include"GameObject.h"
#include"Camera.h"

DrawGraphComp::DrawGraphComp(const std::string& filePath)
{
	texture_ = TextureResourceMgr::Instance().GetTexture(filePath);
}

//	
void DrawGraphComp::Render()
{
	const auto& pos = GetGameObj()->transform.WorldPosition();
	const auto& camera_pos = Camera::Instance().position();
	const auto& camera_size = Camera::Instance().area_size();
	Vector2D<float> draw = pos - camera_pos + (camera_size / 2);



	DrawGraphF(draw.x, draw.y, texture_->GetHandle(), TRUE);
}
