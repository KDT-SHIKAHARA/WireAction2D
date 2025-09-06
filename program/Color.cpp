#include "Color.h"
#include<cmath>
#include"DxLib.h"

/// <summary>
/// �F�̒��ԐF���擾���ăO���f�[�V�����ɂ悤�Ƀu�����h����
/// </summary>
/// <param name="arg_color1"> �ŏ��̐F </param>
/// <param name="arg_color2"> �ς������F </param>
/// <param name="arg_colorLerp"> �u�����h���� </param>
void color::Color::BlendColor(const Color& arg_color1, const Color& arg_color2, const float& arg_colorLerp)
{
	red_ = (int)std::lerp(arg_color1.red_, arg_color2.red_, arg_colorLerp);
	green_ = (int)std::lerp(arg_color1.green_, arg_color2.green_, arg_colorLerp);
	blue_ = (int)std::lerp(arg_color1.blue_, arg_color2.blue_, arg_colorLerp);
}

/// <summary>
/// �N���X���̐F���g���ĐF�R�[�h���擾
/// </summary>
/// <returns>	int�^�̐F�R�[�h	</returns>
int color::Color::GetColorCode()
{
	return GetColor(red_,green_,blue_);
}


