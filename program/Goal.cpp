#include"Goal.h"
#include"PointSaver.h"
#include"ColliderComp.h"
#include"ColliderEvent.h"
#include"HitBOxRenderComp.h"
#include"tag.h"
#include"DrawGraphComp.h"

std::shared_ptr<GameObject> Goal::Create(int num) {
	//	�C���X�^���X
	auto goal = std::make_shared<GameObject>();


	auto filePath = posFile + std::to_string(num) + ".txt";

	//	���W
	auto pos = PointSaver::Instance().GetPoints(filePath);

	for (const auto& p : pos) {
		goal->transform.SetWorldPosition(p);
	}

	//	�����蔻��p
	goal->AddComponent<HitBoxRenderComp>();

	Vector2Df size = { 32,32 };

	//	�����蔻��
	auto collider = goal->AddComponent<ColliderComp>(size);
	collider->isPush.Set(false);

	//	�C�x���g�ʒm
	goal->AddComponent<ColliderEvent>();

	//	�摜
	goal->AddComponent<DrawGraphComp>(texture);

	//	�^�O�̐ݒ�
	goal->SetTag(Tag::GetString(TagType::Goal));



	return goal;
}