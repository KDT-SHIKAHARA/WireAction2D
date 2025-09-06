#pragma once
#include"Component.h"
#include"flag.h"


/// <summary>
/// ジャンプ処理を追加するコンポーネント
/// </summary>
class JumpComp : public Component {
public:
	/// <summary>
	/// キー状態の参照と移動量の設定
	/// </summary>
	void Update()override;

private:
	const float jump_velocity_ = -300.0f;
	Flag canJump = true;

};