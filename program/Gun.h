#pragma once
#include"Component.h"
#include"DrawableComp.h"
#include"vector2d.h"
#include<vector>
#include"transform.h"

//	�e
//	�ړ�
//struct Bullet {
//	Bullet(const Vector2Df& a_position, const Vector2Df& a_velocity,float a_radius, float a_attack);
//	void Update();
//	void Render();
//
//
//	Vector2Df m_position;	 //	���W
//	Vector2Df m_velocity;	 //	�b�Ԃ̈ړ���
//	bool m_enable = true;	 //	�L������
//private:
//	float m_radius = 10;		//	���a�̃T�C�Y
//	float m_attack = 1;		//	�U����
//};


struct Bullet {
	//	������
	Bullet(const Vector2Df& a_position, const Vector2Df& a_target, float a_radius, int a_attack,float a_speed);

	//	�ړ�
	void Update();
	void Render();

	Transform m_transform;		//	���W
	Vector2Df m_target;			//	�^�[�Q�b�g���W
	float m_radius;				//	���a
	float m_speed;				//	�ړ����x
	int m_attack;				//	�U����
	bool m_enable = true;		//	�L������
};


//	���˂ƃC���X�^���X�Ǘ�
class Gun : public Component, public DrawableComp {
	void shoot();	//	���˃��\�b�h

public:
	void Update()override;
	void Render()override;

private:
	std::vector<Bullet> m_bullets;	//	�e�̃R���N�V����
	Vector2Df m_parentPosition;	//	�e�̍��W
	float m_fireRate = 10;		//	���ˊԊu
	float m_fireCooldown;	//	���˂܂ł̃N�[���^�C��

	const float k_bulletRadius = 10;	//	�e�̔��a
	const int k_bulletAttack = 10;		//	�e�̍U����
	const int k_bulletSpeed = 20;		//	�e�̑��x



};
