#include"Needle.h"
#include"ColliderComp.h"
#include"GameObjectMgr.h"
#include"PointSaver.h"
#include"HitBOxRenderComp.h"
#include"tag.h"
#include"DrawGraphComp.h"

//	����
std::shared_ptr<GameObject> Needle::Create(const Vector2Df& a_position, const Vector2Df& a_size) {
	//	�C���X�^���X����
	auto needle = std::make_shared<GameObject>();

	//	���W�ݒ�
	needle->transform.SetWorldPosition(a_position);

	//	�����蔻��
	needle->AddComponent<ColliderComp>(a_size);
	
	//	����p�̎l�p�`�`��
	needle->AddComponent<HitBoxRenderComp>();

	//	�^�O�̐ݒ�
	needle->SetTag(Tag::GetString(TagType::Needle));

	//	�摜�ǂݍ���
	needle->AddComponent<DrawGraphComp>(texture);

	//	�Q�[���I�u�W�F�N�g�̒ǉ�
	GameObjMgr::Instance().AddGameObject(needle);

	return needle;
}


//	�j�̃C���X�^���X�S�Ď擾
void Needle::GetNeedle(int num) {
	auto filePath = posFilePath + std::to_string(num) + ".txt";
	auto positions = PointSaver::Instance().GetPoints(filePath);

	for (const auto& pos : positions) {
		Create(pos, Vector2Df{ 32,32 });
	}

}