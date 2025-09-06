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

	//	�����蔻��
	void CheckCollision() {
	}

private:
	std::vector<std::shared_ptr<Collider>> colliders;	//	�����蔻�������I�u�W�F�N�g�ꗗ


};