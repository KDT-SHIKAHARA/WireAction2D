#pragma once
#include"GameObject.h"
#include<string>

class Goal {
	inline static std::string posFile = "res/goal/pos";
	inline static std::string texture = "res/goal/texture.png";
public:
	static std::shared_ptr<GameObject> Create(int num);
};

//	ゴールのエンティティ作成

//	プレイヤータグと衝突したら反発はせずにScene側に衝突フラグを渡す

//	レイヤー番号は、１で中間レイヤーで