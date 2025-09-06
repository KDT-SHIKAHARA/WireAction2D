#include "Boss.h"
#include "RigidbodyComp.h"
#include "ColliderComp.h"
#include "health.h"
#include "BossState.h"
#include "BossStateController.h"
#include "BossRender.h"
#include "SystemConfig.h"
#include "BossLaser.h"
#include "Scythe.h"

std::shared_ptr<GameObject> Boss::GetGameObj()
{
	std::shared_ptr<GameObject> tmp_GameObj = std::make_shared<GameObject>();
	tmp_GameObj->transform.SetWorldPosition(Vector2D<float>{(float)WINDOW_W / 2,(float)WINDOW_H / 2});
	tmp_GameObj->AddComponent<BossRenderComp>();	//	�`��n
	tmp_GameObj->AddComponent<RigidbodyComp>(1.0,false,true);		//	�������Z
	tmp_GameObj->AddComponent<ColliderComp>(Vector2D<float>{30, 50});		//	�����蔻��
	tmp_GameObj->AddComponent<Health>();			//	�̗�
	tmp_GameObj->AddComponent<BossStateComp>();		//	���
	auto Controller = tmp_GameObj->AddComponent<BossStateController>(); //	��ԊǗ�
	Controller->Start();
	tmp_GameObj->AddComponent<Laser>();
	tmp_GameObj->AddComponent<Scythe>();
	tmp_GameObj->SortLayer();
	return tmp_GameObj;
}

