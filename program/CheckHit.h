#pragma once
#include"vector2d.h"
#include"transform.h"

/// <summary>
/// �������x���d������STL�̃A���S���Y���Ɛ��w�n�͖��g�p
/// ���Z���Y�ȂǂőΉ�
/// </summary>
class CheckHit {
public:
	
	/// <summary>
	/// �]���̕��������g�p�����R�[�h�ʏd��
	/// </summary>
	template<typename T>
	static bool CircleCircle(const Vector2D<T>& a_pos1, float a_radius1, 
							 const Vector2D<T>& a_pos2, float a_radius2) {
		auto length = Get2Distance(a_pos1, a_pos2);
		return length <= a_radius1 + a_radius2;
	}

	/// <summary>
	/// ���������g�p���Ȃ��������x�d��
	/// </summary>
	template<typename T>
	static bool CircleCircleFast(const Vector2D<T>& a_pos1, float a_radius1,
		const Vector2D<T>& a_pos2, float a_radius2) {

		auto dx = a_pos1.x - a_pos2.x;
		auto dy = a_pos1.y - a_pos2.y;
		auto dist2 = dx * dx + dy * dy;
		auto r = a_radius1 + a_radius2;
		return dist2 <= r * r;
	}



	template<typename T>
	static bool BoxBox(const Vector2D<T>& a_pos1, const Vector2D<T>& a_size1,
		const Vector2D<T>& a_pos2, const Vector2D<T>& a_size2) {

		// ���T�C�Y���v�Z
		T halfW1 = a_size1.x * static_cast<T>(0.5);
		T halfH1 = a_size1.y * static_cast<T>(0.5);
		T halfW2 = a_size2.x * static_cast<T>(0.5);
		T halfH2 = a_size2.y * static_cast<T>(0.5);

		// ���S�̍���
		T dx = std::abs(a_pos1.x - a_pos2.x);
		T dy = std::abs(a_pos1.y - a_pos2.y);

		// ������������ꍇ �� false
		if (dx > (halfW1 + halfW2)) return false;
		if (dy > (halfH1 + halfH2)) return false;

		return true;
	}

	template<typename T>
	static bool BoxCircle(const Vector2D<T>& a_pos1, const Vector2D<T>& a_size1,
		const Vector2D<T>& a_pos2, float a_radius2) {

		// ���T�C�Y
		T halfW = a_size1.x * static_cast<T>(0.5);
		T halfH = a_size1.y * static_cast<T>(0.5);

		// ��`�͈͓̔��ɉ~���S�� clamp
		T closestX = (a_pos2.x < a_pos1.x - halfW) ? (a_pos1.x - halfW) :
			(a_pos2.x > a_pos1.x + halfW) ? (a_pos1.x + halfW) : a_pos2.x;
		T closestY = (a_pos2.y < a_pos1.y - halfH) ? (a_pos1.y - halfH) :
			(a_pos2.y > a_pos1.y + halfH) ? (a_pos1.y + halfH) : a_pos2.y;

		// �ŋߖT�_�Ƃ̋����̓��
		T dx = a_pos2.x - closestX;
		T dy = a_pos2.y - closestY;
		T dist2 = dx * dx + dy * dy;

		return dist2 <= static_cast<T>(a_radius2 * a_radius2);
	}



};