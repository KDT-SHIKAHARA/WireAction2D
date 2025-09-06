#include"moveSystem.h"
#include"RigidbodyComp.h"
#include"Time.h"


/// <summary>
/// ゲームオブジェクトのコンポーネントにRigidBodyがついていたら移動処理をする。
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
