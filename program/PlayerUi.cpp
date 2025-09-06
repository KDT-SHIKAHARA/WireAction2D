#include "PlayerUi.h"


/// <summary>
///	�R���|�[�l���g�^���p�����Ă�����X�V�������Ăяo��
/// </summary>
void PlayerUiComp::Update()
{
	for (const auto& ui : ui_) {
		if (auto update =  std::dynamic_pointer_cast<Component>(ui)) {
			update->Update();
		}
	}
}

/// <summary>
/// �S�Ă̕`����Ăяo��
/// </summary>
void PlayerUiComp::Render()
{
	for (const auto& ui : ui_) {
		ui->Render();
	}
}
