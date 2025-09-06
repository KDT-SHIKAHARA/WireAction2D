#pragma once
#include<vector>
#include<memory>
#include"GameObject.h"
#include"singleton.h"


class MoveSystem final : public Singleton<MoveSystem>{
	friend class Singleton<MoveSystem>;

	MoveSystem() = default;
	virtual ~MoveSystem() = default;
public:
	void Update(const std::vector<std::shared_ptr<GameObject>>& gameObjList);


};

