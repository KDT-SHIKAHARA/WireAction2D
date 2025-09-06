#pragma once
#include"Component.h"
#include"DrawableComp.h"
#include"vector2d.h"
#include<vector>
#include"transform.h"

//	弾
//	移動
//struct Bullet {
//	Bullet(const Vector2Df& a_position, const Vector2Df& a_velocity,float a_radius, float a_attack);
//	void Update();
//	void Render();
//
//
//	Vector2Df m_position;	 //	座標
//	Vector2Df m_velocity;	 //	秒間の移動量
//	bool m_enable = true;	 //	有効判定
//private:
//	float m_radius = 10;		//	半径のサイズ
//	float m_attack = 1;		//	攻撃力
//};


struct Bullet {
	//	初期化
	Bullet(const Vector2Df& a_position, const Vector2Df& a_target, float a_radius, int a_attack,float a_speed);

	//	移動
	void Update();
	void Render();

	Transform m_transform;		//	座標
	Vector2Df m_target;			//	ターゲット座標
	float m_radius;				//	半径
	float m_speed;				//	移動速度
	int m_attack;				//	攻撃力
	bool m_enable = true;		//	有効判定
};


//	発射とインスタンス管理
class Gun : public Component, public DrawableComp {
	void shoot();	//	発射メソッド

public:
	void Update()override;
	void Render()override;

private:
	std::vector<Bullet> m_bullets;	//	弾のコレクション
	Vector2Df m_parentPosition;	//	親の座標
	float m_fireRate = 10;		//	発射間隔
	float m_fireCooldown;	//	発射までのクールタイム

	const float k_bulletRadius = 10;	//	弾の半径
	const int k_bulletAttack = 10;		//	弾の攻撃力
	const int k_bulletSpeed = 20;		//	弾の速度



};
