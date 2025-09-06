#pragma once
#include<memory>
#include<vector>
#include<string>
#include"vector2d.h"


#define _XFORM_CREATE std::shared_ptr<Transform>(std::make_shared<Transform>())

enum class Direction {
	Right,
	Left,
	Up,
	Down,
};

class Transform :public std::enable_shared_from_this<Transform> {
	using Xform = std::shared_ptr<Transform>;	//	������shared_ptr
	using Parent = std::weak_ptr<Transform>;	//	�e
	using Children = std::vector<std::shared_ptr<Transform>>;	//	�q���R���N�V����

	Vector2D<float> position_;	//	���W
	float rotation_;			//	�p�x
	Vector2D<float> scale_;		//	�X�P�[��
	Parent parent_;				//	�e
	Children children_;			//	�q��

	Direction angleTupe_ = Direction::Right;

public:	
	Transform() 
		:position_({ 0,0 }), rotation_(0.0f), scale_({ 1.0f,1.0f }){ }

	//	�f�o�b�N
	static inline float ToDeg(float rad) { return rad * (180.0f / 3.1415926f); }
	static inline float ToRad(float deg) { return deg * (3.1415926f / 180.0f); }

	//	�e�̐�c�Ɏ��������邩�ǂ����̔���
	bool IsInAncestorChain(const Xform& arg_new_parent) {
		//	�Q�Ǝ擾
		auto current = parent_.lock();	
		//	�����̐�c�S�Ă�����
		while (current) {
			//	�������猩�đc��ɐV�����e������Ȃ玩���͐�c�ł���
			if (current == arg_new_parent) return true;
			current = current->parent_.lock();
		}
		return false;
	}

	//	�e�̐ݒ�Ɛe���̎������q���ݒ�
	void SetParent(const std::shared_ptr<Transform>& arg_new_parent);

	//	�e�̍폜
	void ClearParent() { SetParent(nullptr); }

	//	�e�̑��ݔ��� true: ���݂��Ă��� false: ���݂��Ă��Ȃ�
	bool HasParent()const { return  !parent_.expired(); }

	//	�e�̎擾
	Xform parent()const { return parent_.lock(); }

	//	�q���̎擾
	Children children()const { return children_; }

	//	�n�c�̎擾
	Xform GetRoot() {
		//	��c�ł��鎩���̃|�C���^�擾
		auto current = shared_from_this();
		//	�����̐e�̐e���������Đ�c�����Ȃ��Ȃ�܂Ō���
		while (auto parent = current->parent_.lock()) {
			//	����Ώۂ��P�Â��
			current = parent;
		}
		//	��ԏ�̊K�w�̃|�C���^��Ԃ��B
		return current;
	}


	//	--------------------------���[�J�����W�A�N�Z�T--------------------------
	void SetPosition(const Vector2D<float>& arg_position) { position_ = arg_position; }
	Vector2D<float> position()const { return position_; }
	void AddPosition(const Vector2D<float>& arg_position) { position_ += arg_position; }
	void SetRotation(const float& arg_rotation) {rotation_= arg_rotation; }
	float rotation()const { return rotation_; }
	void SetScale(const Vector2D<float>& arg_scale) { scale_ = arg_scale; }
	Vector2D<float> scale()const { return scale_; }



	//	--------------------------�O���[�o�����W�A�N�Z�T--------------------------
	//------ �擾------


	//	���[���h�ł̍��W�̎擾
	//	�e������ΐe���玩���̐��l�����炷�B
	//	�e�̉�]�ʂ��l������
	Vector2D<float> WorldPosition()const;

	//	���[���h�ł̉�]�ʂ��擾
	//	�e������ΐe����ǂꂭ�炢��]�����邩
	float WorldRotation()const;

	//	���[���h�ł̃X�P�[���擾
	Vector2D<float> WorldScale()const;


	//	------ �Z�b�g ------


	//	���[���h�ł̍��W�ݒ�
	void SetWorldPosition(const Vector2D<float>& arg_position);

	//	���[���h�ł̃��W�A���p�ݒ�
	void SetWorldRotasion(float arg_rad);

	//	���[���h�ł̃X�P�[���ݒ�
	void SetWorldScale(const Vector2D<float>& arg_scale);


	// ------ ���� ------
	void Translate(const Vector2D<float>& arg_delta_vector) { position_ += arg_delta_vector; }
	void Rotate(const float& deltaRad) { rotation_ += deltaRad; }
	void Scale(const Vector2D<float>& arg_scale) { scale_ = scale_ * arg_scale; }

	// ------ �����x�N�g�� ------

	//	�����Ă�������ւ̈ړ��x�N�g��
	Vector2D<float> Forward()const;

	//	���W���w�肵�Ă��̕����ւ̊p�x���v�Z
	void LookAt(const Vector2D<float>& arg_target);

	//	�w����W�ֈړ��������ړ�����B
	void MoveToTarget(const Vector2D<float>& target, float arg_speed);

	//	�����Ă�������Ɉړ�����B
	void MoveToForward(float arg_speed);

	//	�f�o�b�N���O�ɒǉ�
	void AddDebugLog(const std::string& label = "")const;


	//	-----����-----

	//	�p�x����������擾
	Direction GetAngleType();

};
