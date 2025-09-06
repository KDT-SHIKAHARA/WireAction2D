#pragma once

/// <summary>
/// �`����s�����\�b�h���̃N���X���p������B
/// �X�V�A�`������N���X�ŁA�����I�[�o�[���C�h���Ȃ��Ƃ����Ȃ��ŁA�m�񂵂����ꍇ��
/// �|�C���^�L���X�g�ŕ`�悱�̃N���X���p�����Ă���ꍇ��������������B
/// </summary>
class DrawableComp{
protected:
	int layer_ = 0;
public:
	int GetLayer()const { return layer_; }
	virtual ~DrawableComp() = default;
	virtual void Render() = 0;
};