#include "sword.h"
#include "GameObject.h"
#include "RigidbodyComp.h"
#include "Time.h"
#include "dxlib.h"
#include "ColliderComp.h"
#include "GetColor.h"
#include "PlayerStateController.h"
#include "Camera.h"
#include "GameObjectMgr.h"
#include "tag.h"
#include "Hit.h"
#include "health.h"


/// <summary>
/// GameObjectManager����w�肵���^�O�̃��X�g���쐬����
/// ���̃��X�g�Ɠ����蔻�������
/// </summary>
void Sword::CheckEnemyHit()
{
	auto enemy_list = GameObjMgr::Instance().GetGameObjWithTag(Tag::GetString(TagType::Enemy));

	//	���W����͈͔���
	for (auto enemy : enemy_list){
		//	�����蔻��p�̃R���|�[�l���g�̊m�F
		auto colldier = enemy->GetComponent<ColliderComp>();
		if (!colldier) continue;
		auto size = colldier->size();

		//	�~�Ǝl�p�`�̓����蔻��
		if (Hit::CheckCircleRect(enemy->transform.WorldPosition(), size,
			gameObj_pos_, radius_)) {

			//	�̗̓R���|�[�l���g������āA�����̊Ǘ��R���|�[�l���g���쐬�B
			auto healsh = enemy->GetComponent<Health>();
			if (!healsh) return;
			healsh->Damage(attack_point_);
		}
	}
}

//	�J�n
void Sword::Start() {
	//auto direction = GetGameObj()->transform.GetAngleType();
	//switch (direction) {
	//case Direction::Right:
	//	angle_ = 45.f;	//	�J�n�p�x
	//	angleIncrement_ = -90.f;	//	
	//	break;
	//case Direction::Left:
	//	angle_ = 135.f;
	//	angleIncrement_ = 90.f;
	//	break;
	//case Direction::Up:
	//	angle_ = 60.f;
	//	angleIncrement_ = 70.0f;
	//	break;
	//case Direction::Down:
	//	angle_ = 270.f;
	//	angleIncrement_ = -70.0f;
	//	break;
	//}

	//	�����蔻������鎞�Ԃ̃��Z�b�g
	attackFrame_ = 0;

}


void Sword::Update()
{

	//	���͔���
	auto stateCom = GetGameObj()->GetComponent<StateController>();
	if (!stateCom)return;
	//	���͂��s���邩�ǂ����𔻒肷��
	if (stateCom->CanAttack()) {
		//	���͔���
		if (Input::IsMouseOn(MOUSE_INPUT_LEFT)) {
			Start();
			//	��Ԃ̕ύX
			stateCom->RequestAttack();
		}
	};


	//	�s�����ǂ����𔻒肷��
	if (attackFrame_ >= kAttackFrame_max_) return;

	auto size = GetGameObj()->GetComponent<ColliderComp>()->size();
	//	�Q�[���I�u�W�F�N�g�̍��W�ݒ�
	gameObj_pos_ = GetGameObj()->transform.WorldPosition() + size / 2;

	//	���Ԍo��
	attackFrame_ += Time::deltaTime();

	//	�G�Ɠ����蔻�������



}

void Sword::Render()
{
	if (isFinish())return;

#ifdef _DEBUG
	auto draw = gameObj_pos_ - Camera::Instance().position() + (Camera::Instance().area_size() / 2);
	DrawCircleAA(draw.x, draw.y, radius_, 10, RED, FALSE,3.0f);
#endif // _DEBUG

}
