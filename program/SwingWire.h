#pragma once
#include"DrawableComp.h"
#include"Component.h"
#include"RigidbodyComp.h"


class SwingWire : public Component, public DrawableComp {

	enum class State { Idle, Firing, Swinging, };


	// ��������
	void MoveAnchor();      // �A���J�[�ړ�
	void CheckAnchorCollision();    // �ݒu����
	void CalculateSwing();  // �U��q�^���v�Z
public:
	SwingWire() {};

	//	���˃��\�b�h
	void Start();
	void Fire();			//	���C���[�̔���
	void Release();			//	���C���[����
	void Update()override;	//	�X�V
	void Render()override;	//	�`��
	bool IsFinish() { return isFinish_; }
private:
	State state_ = State::Idle;
	std::shared_ptr<RigidbodyComp> rigidBody_;
	Vector2Df anchorPos_;
	Vector2Df objPos_;
	Vector2Df size_;
	float wireLength_ = 0.0f;  // �A���J�[����v���C���[�܂ł̋���
	
	float initTheta = 0.5f;
	float theta_ = 0.0f;  // �U��q�p�x
	float omega_ = 0.0f;  // �U��q�p���x
	Vector2Df fireDir_;      // ���˕���
	Vector2Df lastVelocity_; // �������ɕێ����鑬�x

	// �萔
	float fireSpeed_ = 2300.0f;    // ���ˑ��x�ipx/s�j
	float maxLength_ = 800.0f;    // ���C���[�ő咷
	float gravity_ = 5000.0f;     // �^���d��
	float damping_ = 0.05f;       // ����
	static constexpr float kInputForce = 0.5f;
	bool isFinish_ = false;
};