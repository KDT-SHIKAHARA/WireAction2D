#include "ui_health.h"
#include "dxlib.h"
#include "health.h"
#include "GetColor.h"



//	�l�p�`��3�d�ɏd�˂�
//	1. �F�t���̓��ߗ���ύX�����l�p�`
//	2. ���F�̂Ȃ����Ƃ������l�p�`
//	3. �F�t���̖{�̂̎l�p�`
void UiPlayerHp::Box(int num)
{
	//	�\��������W
	auto startX = base_pos_x_ + 40;
	//	���[����T�C�Y*�������炵�āA���̈ʒu����Ԋu�����炷
	auto drawX = startX + num * (size_x_ + 10); // �`�悷��X���W

	//	���炷���W
	auto gap = 2;
	//	����ɂ��炷
	auto gap2 = gap * 2;


	//	�\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(drawX, base_pos_y_ + gapY_, drawX + size_x_, base_pos_y_ + size_y_ - gapY_, SKYBLUE, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(drawX - gap, base_pos_y_ + gapY_ +  gap, drawX + size_x_ -  gap, base_pos_y_ + size_y_ - gapY_ +  gap, BLACK, TRUE);
	DrawBox(drawX - gap2, base_pos_y_ + gapY_ + gap2, drawX + size_x_ - gap2, base_pos_y_ + size_y_ - gapY_ + gap2, SKYBLUE, TRUE);


}

void UiPlayerHp::Update()
{
	//	���ݔ���
	if (!healsh_)return;

	//	�̗̓N���X�̎c��̗̑͂����āA���Q�[�W�p�ӂ��邩
	hp_ = healsh_->Current();

}

void UiPlayerHp::Render()
{

	//	���ߗ���ύX���ăx�[�X�ɂȂ�l�p�`��\������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(base_pos_x_, base_pos_y_, base_pos_x_ + base_size_x_, base_pos_y_ + base_size_y_, BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//	�����Ă���悤�Ƀu�����h�ύX

	//	�Q�[�W��p�ӂ��āB�\������
	for (int i = 0; i < hp_; i++) {
		Box(i);
	}

	//	�u�����h��߂�
}
