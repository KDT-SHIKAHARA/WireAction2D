#include "RigidbodyComp.h"
#include "GameObject.h"
#include"Time.h"
#include<cmath>
#include<algorithm>
#include"DebugLog.h"

RigidbodyComp::RigidbodyComp(float arg_mass , Flag arg_isGravity, Flag arg_isStatic)
	:mass_(arg_mass), velocity_(0,0), acceleration_(0,0), gravity_(0,0), totalForce_(0,0), damping_(0.05), isGravity_(arg_isGravity), isGrounded_(false),isStatic_(arg_isStatic)
{
	DebugLog::AddDubug("velocity_x: ", velocity_.x);

}

/// <summary>
/// �O�͂̒ǉ�
/// </summary>
/// <param name="arg_force"> �O�͂̒ǉ� </param>
void RigidbodyComp::AddForce(const Vector2D<float>& arg_force){
	totalForce_ += arg_force;
}

void RigidbodyComp::AddVelocity(const Vector2D<float>& arg_velocity)
{
	velocity_ += arg_velocity;
}

/// <summary>
/// �ړ��x�N�g���̐ݒ�
/// </summary>
/// <param name="arg_velocity"> �ړ��x�N�g���̐ݒ� </param>
void RigidbodyComp::SetVelocity(const Vector2D<float>& arg_velocity){
	velocity_ = arg_velocity;

}

/// <summary>
/// ���������̌v�Z�ƈړ��ʂ̉��Z
/// </summary>
void RigidbodyComp::Update(){

	////	�����ʂ͈̔͐���
	damping_ = std::clamp(damping_, 0.0f, 1.0f);


	//	�e��weak_ptr��lock���Ď擾
	auto GameObj = GetGameObj();
	if (!GameObj) return;

	//	�f���^���Ԏ擾
	const auto& deltaTime = Time::deltaTime();

	//	�����������s����
	if (!isStatic_) {

		//	�d�͎��s����
		if (isGravity_) {

			//	���v�l *= �d�͒萔 * �d�� 
			totalForce_ += Vector2D<float>(0, kGravity * mass_);
		}

		//	�����x = �O�� / ����
		acceleration_ = totalForce_ / mass_;
		velocity_ += acceleration_ ;



		//	�O�͂̃��Z�b�g
		totalForce_.Clear();

	}

	if (isGrounded_) {
		velocity_.x -= velocity_.x * friction_ * deltaTime;
	}
	
	//	������ (���{ - ������)
	//velocity_.x *= (1.0f - damping_);
	velocity_.x *= std::pow(1.0f - damping_, deltaTime);

	//	X���̈ړ��ʂ̐���
	velocity_.x = std::clamp(velocity_.x, -speed_max_, speed_max_);

	// ���x��������������0�ɂ���
	float stopThreshold = 10.0f; // ���̒l�ȉ��Ȃ��~������
	if (std::abs(velocity_.x) < stopThreshold) {
		velocity_.x = 0.0f;
	}


	//	�ړ������́A�ʂ̏ꏊ�ōs���Ĉړ��ʂ����ۑ�����N���X�ɂ���B

	////	�ړ������͏�ɍs��
	//GameObj->transform.AddPosition(velocity_ * deltaTime);


} 
