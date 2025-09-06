#pragma once
#include"vector2d.h"
#include "flag.h"

//	���������݂��Ȃ��I�u�W�F�N�g�Ȃ̂ō���̓������������
//	����̊g�����ƃo�N�̋N���肸�炳���d��
//	�����\���ɂ��Ă����J�������v���C��ɒx��Ĉړ�����Ȃǂ̍\����ǉ�����Ƃ���
//	���Ƃ��炵�₷���悤�ɂƉ�ʔ͈͂̐�������₷������


enum class CameraMode {
	Follow,	//	�Ǐ]
	Fixed,	//	�Œ�
	Script,	//	�O������
	None,	//	�������Ȃ�
};

class Camera {
	Camera();
	virtual ~Camera() = default;

	void ClampPosToMap();

public:
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	static Camera& Instance() {
		static Camera instance;
		return instance;
	}

	Vector2D<float> position()const { return position_; }
	Vector2D<float> area_size()const { return area_size_; }

	//	���[�h�ݒ�
	void SetMode(CameraMode mode) { mode_ = mode; }

	//	�e���[�h�p�ݒ�
	void SetFollowPos(const Vector2D<float>& follow) { follow_position_ = follow; }
	void SetFixedPos(const Vector2D<float>& fixed) { fixed_position_ = fixed; }
	void SetScriptPos(const Vector2D<float>& script) { script_position_ = script; }

	void SetFollowSpeed(float follow_speed) { follow_speed_ = follow_speed; }

	Flag isTargetCam_ = true;	//	�J�����̒Ǐ]�t���O	true: �Ǐ]���� false: �Ǐ]���Ȃ� 

	//	�X�V
	void Update();

	//	�J�������W��ݒ肷��
	void SetPosition(const Vector2D<float>& position) { position_ = position; }

	Vector2Df ScreenToWorld(const Vector2Df& a_screenPos) {
		// �J�����̈ʒu (�X�N���[�������)
		Vector2Df cameraPos = position_;  // �J�����̈ʒu (�J�������W�n)

		// ��ʂ̒��S (�X�N���[������)
		Vector2Df screenCenter = Vector2Df(area_size_.x / 2, area_size_.y / 2);

		// �X�N���[�����W -> �J�������S����W
		Vector2Df localPos = a_screenPos - screenCenter;

		// �J�����̈ʒu�������ă��[���h���W�ɕϊ�
		return localPos + cameraPos;

	};

	//	��ʓ��̔���
private:
	//	�J�������W�A�\���͈�
	Vector2D<float> position_;				//	�J�����̍��W
	Vector2D<float> area_size_;				//	�\������T�C�Y

	//	���[�h�p�f�[�^�@
	Vector2D<float> follow_position_;		//	�Ǐ]����I�u�W�F�N�g���W
	Vector2D<float> fixed_position_;		//	�Œ���W
	Vector2D<float> script_position_;		//	�X�N���v�g������W

	//	���
	CameraMode mode_ = CameraMode::Follow;	//	�J�����̃��[�h

	//	���x
	float follow_speed_ = 5.0f;				//	�J�����̈ړ����x



};

void DrawRotaGraphCam(const Vector2D<float>& pos, float exRate, float angle, int GrHandle, int TransFlag, int ReverseFlagX, int ReverseFlagY);