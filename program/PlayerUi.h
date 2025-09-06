#pragma once
#include<vector>
#include"Component.h"
#include"DrawableComp.h"



/// <summary>
/// ui�N���X���Ǘ�����N���X
/// </summary>
class PlayerUiComp : public Component ,public DrawableComp{
public:
	void Update()override;
	void Render()override;

private:
	std::vector<std::shared_ptr<DrawableComp>> ui_;
};