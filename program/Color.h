#pragma once

#define _COLOR color::

namespace color {

	/// <summary>
	/// �F�̃u�����h�@�\�������Ď��g�Ŏ����̐F��⊮����B
	/// �O���ɐF��n�����߂̃��\�b�h��p�ӂ��āA�R�[�h���~�����Ƃ��̓J���[�R�[�h�擾��
	/// ���\�b�h�Ŏ擾����B
	/// </summary>
	class Color {
		//	�F
		int red_;
		int green_;
		int blue_;
	public:
		//	������
		Color (const int& arg_red = 0, const int& arg_green = 0,const int& arg_blue = 0)
			:red_(arg_red),green_(arg_green),blue_(arg_blue){ }

		//	��ԗ��ŐF�̃u�����h
		void BlendColor(const Color& arg_color1, const Color& arg_color2, const float& arg_colorLerp);

		//	�J���[�R�[�h�擾
		int GetColorCode();

	};

}