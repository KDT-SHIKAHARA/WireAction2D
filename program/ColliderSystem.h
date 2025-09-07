#pragma once
#include<memory>

#include"singleton.h"
#include"GameObject.h"
#include"ColliderComp.h"
#include"CollisionRule.h"

class ColliderSystem : public Singleton<ColliderSystem> {
	friend class Singleton<ColliderSystem>;

	ColliderSystem();
	virtual ~ColliderSystem() = default;

	bool checkCollision(std::shared_ptr<GameObject> obj1, std::shared_ptr<ColliderComp> collider1, std::shared_ptr<GameObject> obj2, std::shared_ptr<ColliderComp> collider2);

	//	: で文字列を分割する
	std::pair<std::string, std::string> splitTag(const std::string& key) {
		//	文字列の検索して分割部のインデックスの取得
		auto pos = key.find(":");
		return { key.substr(0,pos),key.substr(pos + 1) };
	}

	void PushBack(
		std::shared_ptr<GameObject> object1, std::shared_ptr<ColliderComp> collider1,
		std::shared_ptr<GameObject> object2, std::shared_ptr<ColliderComp> collider2,
		bool both);


public:
	void Update();


private:
	CollisionRule rule_;

};
