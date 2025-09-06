#pragma once
#include"Component.h"
#include"vector2d.h"
#include"flag.h"
#include"Time.h"


class RigidbodyComp :public Component {
	static constexpr float kGravity = 9.8f;

	float mass_;						//	�d�� (0�Ȃ瓮���Ȃ�)
	Vector2D<float> velocity_;		//	�ړ��x�N�g��
	Vector2D<float> acceleration_;	//	�����x�x�N�g��(�t���[�����Ƃ̈ړ��ʂ̉��Z��)
	Vector2D<float> gravity_;		//	�d�́i�������ɂ��Ή��ł���悤�Ɂj
	Vector2D<float> totalForce_;	//	�N���X�O�̈ړ��ʂ̑S��(�ړ��A���C���[�Ȃ�)
	float damping_;					//	������
	float friction_ = 10.0f;			//	���C
	const float speed_max_ = 1000.0f;
public:
	Flag isGravity_;				//	�d�̓t���O true: �d�͉��Z false: ���d��
	Flag isGrounded_;				//	�n�ʂɐݒu����@true: �ݒu���Ă���	false:�ݒu���ĂȂ�
	Flag isStatic_;					//	�����������s�����ǂ��� true: �s��Ȃ� false: �s��

	RigidbodyComp(float arg_mass = 1.0f, Flag arg_isGravity = true, Flag arg_isStatic = false);
	virtual ~RigidbodyComp() = default;

	//	�O�͂̉��Z
	void AddForce(const Vector2D<float>& arg_force);

	//	�ړ��x�N�g���ǉ�
	void AddVelocity(const Vector2D<float>& arg_velocity);

	//	�ړ��x�N�g���Z�b�g
	void SetVelocity(const Vector2D<float>&arg_velocity);

	//	�ړ��x�N�g���̎擾
	Vector2D<float> velocity()const { return velocity_ * Time::deltaTime(); }
	Vector2Df velocityRaw()const { return velocity_; }

	//	�X�V
	void Update()override;


}; // class

