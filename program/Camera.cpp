#include "Camera.h"
#include "SystemConfig.h"
#include "Time.h"
#include "DebugLog.h"
#include "MapManager.h"

Camera::Camera(){
	//	初期座標の設定
	position_ = { (float)WINDOW_W / 2 , (float)WINDOW_H / 2 };
	//	表示範囲の設定
	area_size_ = { (float)WINDOW_W ,(float)WINDOW_H};

	//	
	follow_position_ = position_;
}

//	カメラ座標をマップ外に生かせない処理
void Camera::ClampPosToMap(){

	auto map_size = MapManager::Instance().ChipNum() * MapManager::Instance().ChipSize();



	//	半分のサイズ
	auto half = area_size_ / 2;
	
	//	横軸
	if (position_.x < half.x) {
		position_.x = half.x;
	}
	else if (position_.x > map_size.x - half.x) {
		position_.x = map_size.x - half.x;
	}


	//	縦軸
	if (position_.y < half.y) {
		position_.y = half.y;
	}
	else if (position_.y > map_size.y - half.y) {
		position_.y = map_size.y - half.y;
	}
}

/// <summary>
/// モードによってカメラの座標を追従させるかを変更させる
/// 追従状態などの状態を一括管理したいので
/// </summary>
void Camera::Update() {

	switch (mode_) {
	case CameraMode::Follow:
		position_.x = follow_position_.x;
		position_.y = follow_position_.y;

		DebugLog::Log("camera_x:", position_.x, 0, 80);
		DebugLog::Log("camera_y:", position_.y, 0, 100);


		//position_ = { position_.x,(float)WINDOW_H / 2 + 100 };
		break;
	case CameraMode::Fixed: 
		DebugLog::Log("camera_x:", position_.x, 0, 80);
		DebugLog::Log("camera_y:", position_.y, 0, 100);
		position_ = { (float)WINDOW_W / 2 , (float)WINDOW_H / 2 };

		break;
	case CameraMode::Script:
		break;
	case CameraMode::None:
		break;
	}

	ClampPosToMap();
}

/// <summary>
///	カメラ座標を考慮して画像を描画する
/// </summary>
/// <param name="pos"></param>
/// <param name="exRate"></param>
/// <param name="angle"></param>
/// <param name="GrHandle"></param>
/// <param name="TransFlag"></param>
/// <param name="ReverseFlagX"></param>
/// <param name="ReverseFlagY"></param>
void DrawRotaGraphCam(const Vector2D<float>& pos, float exRate, float angle, int GrHandle, int TransFlag, int ReverseFlagX, int ReverseFlagY)
{
	auto draw = pos - Camera::Instance().position() + (Camera::Instance().area_size() / 2);
	DrawRotaGraphF(draw.x, draw.y, exRate, angle, GrHandle, TransFlag, ReverseFlagX, ReverseFlagY);
}
