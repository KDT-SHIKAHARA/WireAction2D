#include "GameObject.h"
#include <algorithm>

/// <summary>
/// components�̑S�Ă̍X�V���Ă�
/// </summary>
void GameObject::Update(){
	//	�S�Ă̍X�V�������Ăяo��
	for (auto& [_, comp] : components_) {
		if (comp) comp->Update();
	}
}


/// <summary>
/// components�̕`�������N���X��Render��S�ČĂ�
/// </summary>
void GameObject::Render(){
	////	first��second�ŕ���(first�͍���g��Ȃ��̂�[_]�Ŗ��O��t���ĂȂ�)
	//for (auto& [_, comp] : components_) {
	//	//	���N���X�ɕ`�悪���邩���L���X�g���Ċm�F true: �p�����Ă��� false: �p�����Ă��Ȃ� 
	//	if (auto drawable = std::dynamic_pointer_cast<DrawableComp>(comp)) {
	//		//	�`��
	//		drawable->Render();
	//	}
	//}

	for (auto drawable : drawableComps_) {
		drawable->Render();
	}
}

/// <summary>
/// �`��n�R���|�[�l���g��layer��������l���ɕ��ёւ���
/// �ǂ����ł��Ȃ炸�Ă�ł� 
/// </summary>
void GameObject::SortLayer()
{
	std::sort(drawableComps_.begin(), drawableComps_.end(),
		[](const std::shared_ptr<DrawableComp>& first, const std::shared_ptr<DrawableComp>& second) {
			return first->GetLayer() < second->GetLayer();
		});
}



