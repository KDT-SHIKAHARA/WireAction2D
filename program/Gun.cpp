#include "Gun.h"
#include "GameObjectMgr.h"
#include "ColliderComp.h"
#include "Hit.h"
#include "health.h"
#include "GetColor.h"
#include "input.h"
#include "PlayerStateController.h"
#include "Camera.h"

#include<DxLib.h>

//Bullet::Bullet(const Vector2Df& a_position, const Vector2Df& a_velocity, float a_radius, float a_attack)
//	:m_position(a_position), m_velocity(a_velocity), m_radius(a_radius), m_attack(a_attack)
//{
//
//}
//
//void Bullet::Update() {
//	if (!m_enable) return;
//	m_position += m_velocity;
//	//	当たり判定
//	auto enemyList = GameObjMgr::Instance().GetGameObjWithTag(Tag::GetString(TagType::Enemy));
//	for (auto enemy : enemyList) {
//		//	当たり判定用のコンポーネントの確認
//		auto colldier = enemy->GetComponent<ColliderComp>();
//		if (!colldier) continue;
//		auto size = colldier->size();
//		//	円と四角形の当たり判定
//		if (Hit::CheckCircleRect(enemy->transform.WorldPosition(), size,
//			m_position, m_radius)){
//			//	体力コンポーネントを作って、生存の管理コンポーネントを作成。
//			auto healsh = enemy->GetComponent<Health>();
//			if (!healsh) return;
//			healsh->Damage(m_attack);
//		}	//	if
//	} // for
//} // func
//
//void Bullet::Render() {
//	DrawCircleAA(m_position.x, m_position.y, m_radius, 50, BLUE, TRUE);
//}

//	コレクションに追加して
//	マウス座標から移動ベクトルを設定する
//	入力管理と呼び出す数は外で制御。生成だけ　
void Gun::shoot()
{


	//	マウス座標をターゲット座標に
	Vector2Df target{ (float)Input::MouseX(),(float)Input::MouseY() };
	target = Camera::Instance().ScreenToWorld(target);

	//	インスタンス生成
	m_bullets.push_back(Bullet{ m_parentPosition ,target, (float)k_bulletRadius ,(int)k_bulletAttack,(float)k_bulletSpeed });

}

void Gun::Update()
{
	//	親座標の取得
	m_parentPosition = GetGameObj()->transform.WorldPosition();


	if (m_fireCooldown > 0) {
		m_fireCooldown--;
	}
	else {
		//	入力判定
		if (Input::IsMousePressed(MOUSE_INPUT_LEFT)) {
			shoot();
			m_fireCooldown = m_fireRate;
		}

	}


	for (auto& bullet : m_bullets) {
		bullet.Update();
	}


	for (auto& bullet : m_bullets) {
		//	当たり判定
		auto enemyList = GameObjMgr::Instance().GetGameObjWithTag(Tag::GetString(TagType::Enemy));
		for (auto enemy : enemyList) {
			//	当たり判定用のコンポーネントの確認
			auto colldier = enemy->GetComponent<ColliderComp>();
			if (!colldier) continue;
			auto size = colldier->size();

			//	円と四角形の当たり判定
			if (Hit::CheckCircleRect(enemy->transform.WorldPosition(), size,
				bullet.m_transform.WorldPosition(), k_bulletRadius)) {

				bullet.m_enable = false;

				//	体力コンポーネントを作って、生存の管理コンポーネントを作成。
				auto healsh = enemy->GetComponent<Health>();
				if (!healsh) return;
				healsh->Damage(k_bulletAttack);
			}
		}

	}

	//	削除
	m_bullets.erase(
		std::remove_if(m_bullets.begin(), m_bullets.end(), [](const Bullet& b) {
			return !b.m_enable;
			}),
		m_bullets.end()
	);
}

void Gun::Render()
{
	for (auto& bullet : m_bullets) {
		bullet.Render();
	}

}

//	初期化
Bullet::Bullet(const Vector2Df& a_position, const Vector2Df& a_target, float a_radius, int a_attack, float a_speed)
:m_target(a_target),m_radius(a_radius),m_attack(a_attack), m_speed(a_speed)
{
	//	座標設置
	m_transform.SetWorldPosition(a_position);
	//	2点間の座標から移動する角度を取得
	m_transform.LookAt(m_target);

}

void Bullet::Update() {
	if (!m_enable) return;
	//	内部で持っている角度の方向に移動する
	m_transform.MoveToForward(m_speed);
}

void Bullet::Render() {
	if (!m_enable) return;
	auto pos = m_transform.WorldPosition() - Camera::Instance().position() + (Camera::Instance().area_size() / 2);
	DrawCircleAA(pos.x, pos.y, m_radius, 50, BLUE, TRUE);
}