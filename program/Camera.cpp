#include "Camera.h"
#include "SystemConfig.h"
#include "Time.h"
#include "DebugLog.h"
#include "MapManager.h"

Camera::Camera(){
	//	�������W�̐ݒ�
	position_ = { (float)WINDOW_W / 2 , (float)WINDOW_H / 2 };
	//	�\���͈͂̐ݒ�
	area_size_ = { (float)WINDOW_W ,(float)WINDOW_H};

	//	
	follow_position_ = position_;
}

//	�J�������W���}�b�v�O�ɐ������Ȃ�����
void Camera::ClampPosToMap(){

	auto map_size = MapManager::Instance().ChipNum() * MapManager::Instance().ChipSize();



	//	�����̃T�C�Y
	auto half = area_size_ / 2;
	
	//	����
	if (position_.x < half.x) {
		position_.x = half.x;
	}
	else if (position_.x > map_size.x - half.x) {
		position_.x = map_size.x - half.x;
	}


	//	�c��
	if (position_.y < half.y) {
		position_.y = half.y;
	}
	else if (position_.y > map_size.y - half.y) {
		position_.y = map_size.y - half.y;
	}
}

/// <summary>
/// ���[�h�ɂ���ăJ�����̍��W��Ǐ]�����邩��ύX������
/// �Ǐ]��ԂȂǂ̏�Ԃ��ꊇ�Ǘ��������̂�
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
///	�J�������W���l�����ĉ摜��`�悷��
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
