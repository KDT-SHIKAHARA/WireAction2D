#include "PlayerUi.h"


/// <summary>
///	コンポーネント型を継承していたら更新処理を呼び出す
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
/// 全ての描画を呼び出す
/// </summary>
void PlayerUiComp::Render()
{
	for (const auto& ui : ui_) {
		ui->Render();
	}
}
