#include "transform.h"
#include<cmath>
#include"DebugLog.h"
#include"GameObject.h"
#include "RigidbodyComp.h"

// ==================================================================
// �t�@�C����	�Ftransform.h
// �����		�F2025.7.15
// �X�V��		�F2025.7.15
// �����		�F�����ishikahara�j
// �T�v			�F���W�A��]�A�X�P�[���̊Ǘ��⑀�������N���X
// �ύX����		�F�Ȃ�
// ===================================================================


/// <summary>
/// �e�����݂��Ă�����폜���āA���݂��Ă��Ȃ�������ǉ�������B
/// �܂��z�Q�ƂɂȂ�Ȃ��悤�Ɏ����̐�c�ɐe�ɂ������I�u�W�F�N�g�����݂��Ă��Ȃ����𔻒f
/// </summary>
/// <param name="arg_new_parent"> �V�����e�̃|�C���^ </param>
void Transform::SetParent(const std::shared_ptr<Transform>& arg_new_parent){
	//	�V�����e���������ǂ����̔��聕�V�����e�������̐�c�ɂ����玩���͐�c�Ȃ̂�
	//	��c���e�ɂȂ�̂͂��������̂Ŗh�~�p�̃��\�b�h
	//	������e�̐ݒ�����Ȃ��B�z�Q�Ɩh�~
	if (arg_new_parent.get() == this|| IsInAncestorChain(arg_new_parent)) {
		return;
	}

	//�@�e�����݂��Ă�����
	if (const auto& parent_ptr = parent_.lock()) {
		auto& parent_children = parent_ptr->children_;
		parent_children.erase(std::remove(parent_children.begin(), parent_children.end(), shared_from_this()), parent_children.end());
	}

	//	�e�̕ύX
	parent_ = arg_new_parent;
	//	�e��nullptr����Ȃ����
	if (arg_new_parent) {
		arg_new_parent->children_.push_back(shared_from_this());
	}

}



/// <summary>
/// ���ۂ̍��W�擾
/// </summary>
/// <returns> ���ۂ̍��W </returns>
Vector2D<float> Transform::WorldPosition() const{
	//	�e�|�C���^�擾
	auto parent_ptr = parent();
	//	���݂��Ă��Ȃ���������W��Ԃ�
	if (!parent_ptr) return position_;
	//	���݂��Ă�����e�̊p�x����Ƃ��č��W�������B
	Vector2D<float> scalePosition = (Vector2D<float>)position_ * parent_ptr->WorldScale();
	return parent_ptr->WorldPosition() + (scalePosition.Rotated(parent_ptr->WorldRotation()));
}

/// <summary>
/// �p�x�̎擾
/// </summary>
/// <returns></returns>
float Transform::WorldRotation() const{
	//	�e�|�C���^�擾
	const auto& parent_ptr = parent_.lock();
	//	���݂��Ă�����e����rota���������p�x : �����̊p�x
	return parent_ptr ? (parent_ptr->WorldRotation() + rotation_) : rotation_;
}

/// <summary>
/// �T�C�Y�̔{��
/// </summary>
/// <returns> �e������ΐe�̊p�x </returns>
Vector2D<float> Transform::WorldScale() const{
	//	�e�|�C���^�擾
	const auto& parent_ptr = parent_.lock();
	//	���݂��Ă��Ȃ���΃X�P�[�������̂܂ܕԂ�
	if (!parent_ptr) return scale_;
	//	���݂��Ă���ΐe��e�̔䗦*�����̔䗦��Ԃ��B
	return (parent_ptr->WorldScale() * scale_);
}

/// <summary>
/// �e�����Ȃ���Ε��ʂɍ��W���Z�b�g����
/// �e������ΐe�̈ړ��x�N�g������ɂ��āA�ړ�������
/// </summary>
/// <param name="worldPosition"></param>
void Transform::SetWorldPosition(const Vector2D<float>& worldPosition){
	//	�e�|�C���^�擾
	const auto& parent_ptr = parent_.lock();
	//	���݂��Ă��Ȃ���΍��W�����̂܂܃Z�b�g
	if (!parent_ptr) {
		position_ = worldPosition;
		return;
	}

	//	���݂��Ă����
	//	�e�̈ʒu�Ɗp�x����Ƃ��ċ�ԍ��W��ݒ肷��

	//	�����v�Z
	Vector2D<float> delta = worldPosition - parent_ptr->WorldPosition();
	//	��������p�x���g���Ĉړ��x�N�g�����쐬(�e�̉�]�̑ŏ���)
	Vector2D<float> unrot = delta.Rotated(-parent_ptr->WorldRotation());
	
	// ��ԍ��W�̐ݒ�(�e�̃X�P�[���ʒu�����炷�A�䗦���킹)
	position_ = (unrot / parent_ptr->WorldScale());

}

/// <summary>
/// �e�����Ȃ���Ε��ʂɊp�x�̐ݒ�
/// �e������ΐe�̊p�x���玩���̊p�x�����炷(�e��]�ŏ���)
/// </summary>
/// <param name="rad"></param>
void Transform::SetWorldRotasion(float rad){
	//	�e�|�C���^�擾
	auto parent_ptr = parent_.lock();

	//	parent_ptr ��nullptr���ǂ���
	//	true: �e���玩���̉�]���ł��������p�x�@false: �p�x�����̂܂�
	rotation_ = parent_ptr ? rad - parent_ptr->WorldRotation() : rad;
}

/// <summary>
/// �e�����Ȃ���Ε��ʂɃX�P�[���̐ݒ�
/// �e������ΐe�̃X�P�[�� / �����̃X�P�[���ŃT�C�Y
/// </summary>
/// <param name="arg_scale"> �ݒ肵���������̃X�P�[�� </param>
void Transform::SetWorldScale(const Vector2D<float>& arg_scale){
	//	�e�|�C���^�擾
	const auto& parent_ptr = parent_.lock();

	//	parent_ptr ��nullptr���ǂ���
	/// true: �e�̃X�P�[�� / �����̃X�P�[���ŃT�C�Y false: ���̂܂ܕύX
	scale_ = parent_ptr ? (arg_scale / parent_ptr->WorldScale()): arg_scale;
}

/// <summary>
/// �����Ă�������Ɉړ��x�N�g�����쐬�@
/// </summary>
/// <returns> �����x�N�g�� </returns>
Vector2D<float> Transform::Forward() const{
	return { std::cosf(WorldRotation()),std::sinf(WorldRotation()) };
}

/// <summary>
/// �n���ꂽ���W�ɑ΂��Ă̊p�x���v�Z����
/// </summary>
/// <param name="arg_target"> �Ώۂ̍��W </param>
void Transform::LookAt(const Vector2D<float>& arg_target){
	//	�ړ��x�N�g��
	Vector2D dir = arg_target - WorldPosition();
	//	�p�x
	float angle = std::atan2f(dir.y, dir.x);
	//	�Z�b�g
	SetWorldRotasion(angle);
}

/// <summary>
/// �w����W�ֈړ��������ړ�����B
/// �������Z��������Ώۂ̍��W�ɂ���B
/// </summary>
/// <param name="target"> �w����W </param>
/// <param name="arg_speed"> �ړ����x </param>
void Transform::MoveToTarget(const Vector2D<float>& target, float arg_speed){
	//	�ړ��x�N�g���쐬
	Vector2D<float> dir = target - WorldPosition();
	//	�����擾
	float length = dir.GetLength();

	//	�����ƈړ����x�̔���
	
	//	���� < �ړ����x �Ȃ�w����W�ɂ���
	if (length <= arg_speed) {
		SetWorldPosition(target);
		return;
	}

	//	�Ⴄ�Ȃ琳�K�������Ĉړ����x��������
	SetWorldPosition(WorldPosition() + (dir.Normalize() * arg_speed));

}

/// <summary>
/// �����Ă�������Ɉړ�����B
/// �����̃Z�b�g�Ȃǂ͂��̃��\�b�h���Ăяo���O�ɃZ�b�g����B
/// �����ƒǐՂ�����Ȃ�^�[�Q�b�g�Z�b�g�̃��\�b�h����ɌĂяo��
/// </summary>
/// <param name="arg_speed"> �ړ����x </param>
void Transform::MoveToForward(float arg_speed){
	//	������������x�N�g�����쐬
	Vector2D<float> rot_vector = Forward();

	//	���ݍ��W�Ɉړ��x�N�g���𑫂�
	SetWorldPosition(WorldPosition() + rot_vector * arg_speed);
}

/// <summary>
/// �f�o�b�N���O�ɍ��W�Ɗp�x�ƃX�P�[����\������
/// </summary>
/// <param name="label"></param>
void Transform::AddDebugLog(const std::string& label) const{
	DebugLog::AddDubug(label + " position.x:", position_.x);
	DebugLog::AddDubug(label + " position.y:", position_.y);
	DebugLog::AddDubug(label + " rotation:", rotation_);
	DebugLog::AddDubug(label + " scale.x:", scale_.x);
	DebugLog::AddDubug(label + " scale.y:", scale_.y);
	DebugLog::AddDubug(label + " HasParent:", HasParent());
}

//	�������擾
Direction Transform::GetAngleType()
{

	// �p�x�� -�� �` �� �͈̔͂ɐ��K��
	while (rotation_ <= -PI) rotation_ += 2 * PI;
	while (rotation_ > PI) rotation_ -= 2 * PI;

	if (rotation_ > -PI / 4 && rotation_ <= PI / 4) {
		return Direction::Right;
	}
	else if (rotation_ > PI / 4 && rotation_ <= 3 * PI / 4) {
		return Direction::Up;
	}
	else if (rotation_ <= -PI / 4 && rotation_ > -3 * PI / 4) {
		return Direction::Down;
	}
	else {
		// �c��͍������i3��/4 ? �� �܂��� -�� ? -3��/4�j
		return Direction::Left;
	}
}




