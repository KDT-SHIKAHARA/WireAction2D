#pragma once

//	�쐬��: 2025.7.18
//	�X�V��:	2025.7.18
//	�쐬��:	kirito shikahara


/// <summary>
/// ����͋�`���m���Ȃ��̂ŕK�v�͂Ȃ����ǉ~�Ƃ̓����蔻������Ƃ���ǉ��ł���悤�ɍ���Ă����܂�
/// �����C���������Ƃ��͂�����g���Ă��������A�����̉���
/// </summary>
enum class TileShape {
	None,
	Rect,
	Circle,
};



/// <summary>
/// �}�b�v�^�C���͂��̃N���X�������}�b�v�f�[�^�N���X�ł������ڒ��g������Ȃ��̂�struct��
/// �J�v�Z�������d������Ȃ�class�ŃA�N�Z�T�����܂��B
/// </summary>
struct Tile {
	int id = 0;			//	��ʎ���
	TileShape shape = TileShape::None;	//	�`
	bool isCollision = true;	//	�����蔻����s�����ǂ���
};

