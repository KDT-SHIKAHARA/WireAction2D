#pragma once
#include"GameObject.h"

enum class PlayerState {
	idle,//	待機
	move,//	移動
	jump,//	ジャンプ
	attack,//	攻撃
	swing,//	スイングワイヤー　
	dive,//	ダイブワイヤー
	MAX,//	最大数
};

class Player :public GameObject {
	PlayerState state;
public:
	Player();
	Player(int num);
	virtual ~Player() = default;

	//	コンポーネント追加
	void SetComponent();

	//	更新、描画71
	void Update()override;
	void Render()override;

private:
	std::string posFile = "res/player/pos/";
};