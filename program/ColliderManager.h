#pragma once
#include<vector>
#include<memory>
#include"CircleCollider.h"

class ColliderManager {
	ColliderManager() = default;
	virtual ~ColliderManager() = default;

public:
	ColliderManager(const ColliderManager&) = delete;
	ColliderManager& operator=(const ColliderManager&) = delete;

	static ColliderManager& Instance() {
		static ColliderManager instance;
		return instance;
	}

	//	
	void AddCollider(const std::shared_ptr<Collider>& arg_collider) {
		colliders.push_back(arg_collider);
	}

	//	当たり判定
	void CheckCollision() {
	}

private:
	std::vector<std::shared_ptr<Collider>> colliders;	//	当たり判定をするオブジェクト一覧


};