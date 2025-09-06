#pragma once
#include"Circle.h"

struct Rect {
	float x, y, w, h = 0;

	bool IsCollision(const Rect& other) {
		return !(x + w <= other.x || other.x + other.w <= x ||
			y + h <= other.y || other.y + other.h <= y);
	}

    //  �l�p�`�Ɖ~�̓����蔻��
	bool IsCollisionCircle(const Circle& circle)const {
        // ��`�̒��S���W
        float centerX = x + w * 0.5f;
        float centerY = y + h * 0.5f;

        // �~�̒��S�Ƌ�`���S�̋����̐�Βl�iX,Y�j
        float distX = std::abs(circle.x - centerX);
        float distY = std::abs(circle.y - centerY);

        // �~�̒��S����`�͈̔͊O�����Ȃ�Փ˂Ȃ�
        if (distX > (w * 0.5f + circle.radius)) return false;
        if (distY > (h * 0.5f + circle.radius)) return false;

        // �~�̒��S����`�̕��܂��͍����͈͓̔��Ȃ�Փ˂���
        if (distX <= (w * 0.5f)) return true;
        if (distY <= (h * 0.5f)) return true;

        // �~�̒��S�����`�̊p�܂ł̋�����2����v�Z
        float cornerDistSq = (distX - w * 0.5f) * (distX - w * 0.5f) +
            (distY - h * 0.5f) * (distY - h * 0.5f);

        // �p�Ƃ̋��������a�ȓ��Ȃ�Փ˂���
        return cornerDistSq <= (circle.radius * circle.radius);
	}
};