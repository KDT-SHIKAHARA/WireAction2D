#include"moveSystem.h"
#include"RigidbodyComp.h"
#include"Time.h"


/// <summary>
/// �Q�[���I�u�W�F�N�g�̃R���|�[�l���g��RigidBody�����Ă�����ړ�����������B
/// </summary>
/// <param name="gameObj"></param>
void MoveSystem::Update(const std::vector<std::shared_ptr<GameObject>>& gameObjList)
{
	for (auto& gameObj : gameObjList) {
		auto rigid = gameObj->GetComponent<RigidbodyComp>();
		if (!rigid) continue;
		gameObj->transform.AddPosition(rigid->velocity());

	}
}
