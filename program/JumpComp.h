#pragma once
#include"Component.h"
#include"flag.h"


/// <summary>
/// �W�����v������ǉ�����R���|�[�l���g
/// </summary>
class JumpComp : public Component {
public:
	/// <summary>
	/// �L�[��Ԃ̎Q�Ƃƈړ��ʂ̐ݒ�
	/// </summary>
	void Update()override;

private:
	const float jump_velocity_ = -300.0f;
	Flag canJump = true;

};