#pragma once
#include<memory>

class GameObject;

/// <summary>
/// ‘S‚Ä‚Ìcomponent‚ÌŠî’ê
/// </summary>
class Component {
public:
	virtual ~Component() = default;
	virtual void Update() = 0;
	void SetGameObj(const std::shared_ptr<GameObject>& arg_gameObj) { gameObj_ = arg_gameObj; }
	std::shared_ptr<GameObject> GetGameObj()const { return gameObj_.lock(); }
protected:
	std::weak_ptr<GameObject> gameObj_;
};

