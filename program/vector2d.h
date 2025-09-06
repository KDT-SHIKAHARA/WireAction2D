#pragma once
#include<math.h>
#include<DxLib.h>
#include<cmath>


#define PI        3.14159265f
#define RadToDeg  57.29577951f
#define DegToRad  0.017453293f



template <typename T>
class Vector2D {
public:
	T x;
	T y;

	Vector2D(T arg_x = 0, T arg_y = 0) {
		x = arg_x;
		y = arg_y;
	}

	//	reset
	void Clear() {
		x = y = 0.0; 
	}
	//	set
	void Set(T arg_x, T arg_y) { 
		x = arg_x; y = arg_y; 
	}
	void Set(Vector2D& value) { 
		x = value.x; y = value.y; 
	}


	float GetLength() const {
		return sqrtf(x * x + y * y);
	}


	Vector2D<T> Normalize() {
		float length = GetLength();
		if (length > 0.0f) {
			x = x / length;
			y = y / length;
		}
		return { x,y };
	}

	void SetLength(float arg_length) {
		Normalize();
		x = x * arg_length;
		y = y * arg_length;
	}


	// Dot�ς��v�Z���郁�\�b�h�i�����K�{�j
	float Dot(const Vector2D<T>& other) const {
		return x * other.x + y * other.y;
	}



	// ope =
	Vector2D& operator  = (const Vector2D& value) {
		x = value.x; y = value.y;
		return *this;
	}
	// ope += 
	Vector2D& operator += (const Vector2D& value) {
		x += value.x; y += value.y;
		return *this;
	}
	// ope -=
	Vector2D& operator -= (const Vector2D& value) {
		x -= value.x; y -= value.y;
		return *this;
	}

	// ope *= 
	Vector2D& operator *= (const T value) {
		x *= value;
		y *= value;
		return *this;
	}

	// ope /=
	Vector2D& operator /= (const T value) {
		x /= value;
		y /= value;
		return *this;
	}

	//	��]
	Vector2D Rotated(const float& radians) {
		float cosR = std::cos(radians);
		float sinR = std::sin(radians);
		//	�v�Z��
		// X * cosR - Y * sinR
		// X * sinR + Y * cosR
		return { x * cosR - y * sinR,x * sinR + y * cosR };
	}
};

// ope +
template <typename T>
Vector2D<T> operator + (const Vector2D<T>& value_1, const Vector2D<T>& value_2) {
	Vector2D<T> ret;
	ret.x = value_1.x + value_2.x;
	ret.y = value_1.y + value_2.y;
	return ret;
}

// ope +
template <typename T,typename N>
Vector2D<T> operator + (const Vector2D<T>& value_1, const Vector2D<N>& value_2) {
	Vector2D<T> ret;
	ret.x = value_1.x + value_2.x;
	ret.y = value_1.y + value_2.y;
	return ret;
}

// ope -
template <typename T>
Vector2D<T> operator - (const Vector2D<T>& value_1, const Vector2D<T>& value_2) {
	Vector2D<T> ret;
	ret.x = value_1.x - value_2.x;
	ret.y = value_1.y - value_2.y;
	return ret;

}

// ope -
template <typename T,typename N>
Vector2D<N> operator - (const Vector2D<T>& value_1, const Vector2D<N>& value_2) {
	Vector2D<N> ret;
	ret.x = value_1.x - value_2.x;
	ret.y = value_1.y - value_2.y;
	return ret;

}

// ope *
template <typename T>
Vector2D<T> operator * (const Vector2D<T>& value_1, const Vector2D<T>& value_2) {
	Vector2D<T> ret;
	ret.x = value_1.x * value_2.x;
	ret.y = value_1.y * value_2.y;
	return ret;

}

// ope *
template <typename T,typename N>
Vector2D<T> operator * (const Vector2D<T>& value_1, const Vector2D<N>& value_2) {
	Vector2D<T> ret;
	ret.x = value_1.x * value_2.x;
	ret.y = value_1.y * value_2.y;
	return ret;

}


// ope *
template <typename T, typename N>
Vector2D<T> operator * (const Vector2D<T>& value_1, const N& value_2) {
	Vector2D<T> ret;
	ret.x = value_1.x * value_2;
	ret.y = value_1.y * value_2;
	return ret;

}

// ope *
template <typename T>
Vector2D<T> operator * (const Vector2D<T>& value_1, const T& value_2) {
	Vector2D<T> ret;
	ret.x = value_1.x * value_2;
	ret.y = value_1.y * value_2;
	return ret;

}



// ope /
template <typename T>
Vector2D<T> operator / (const Vector2D<T>& value_1, const Vector2D<T>& value_2) {
	Vector2D<T> ret;
	ret.x = value_1.x / value_2.x;
	ret.y = value_1.y / value_2.y;
	return ret;
}

// ope /
template <typename T,typename N>
Vector2D<N> operator / (const Vector2D<T>& value_1, const Vector2D<N>& value_2) {
	Vector2D<N> ret;
	ret.x = value_1.x / value_2.x;
	ret.y = value_1.y / value_2.y;
	return ret;
}

// ope /
template <typename T, typename N>
Vector2D<T> operator / (const Vector2D<T>& value_1, const N & value_2) {
	Vector2D<T> ret;
	ret.x = value_1.x / value_2;
	ret.y = value_1.y / value_2;
	return ret;
}



// ope /
template <typename T>
Vector2D<int> operator / (const Vector2D<T>& value_1, const int& value_2) {
	Vector2D<int> ret;
	ret.x = value_1.x / value_2;
	ret.y = value_1.y / value_2;
	return ret;
}

// distance
template <typename T>
T Get2Distance(const Vector2D<T>& value_1, const Vector2D<T>& value_2) {
	T x = value_1.x - value_2.x;
	T y = value_1.y - value_2.y;
	T distance = sqrtf(x * x + y * y);
	return distance;
}

/// <summary>
///	��_�̍��W�ƎO�p�֐����g���ĂP�t���[�����Ƃ̈ړ��ʂ�Ԃ��֐�
/// </summary>
/// <typeparam name="T">		���W�n�Ŏg���Ă���^(float or int)�@</typeparam>
/// <param name="Pos">			�ړ����鑤�̍��W					</param>
/// <param name="TargetPos">	�ړ�����邪���̍��W				</param>
/// <returns>					�ړ���								</returns>
template<typename T>
Vector2D<T> SetTarget(const Vector2D<T>& Pos,const Vector2D<T>& TargetPos) {
	float angle = atan2f((TargetPos.y - Pos.y), (TargetPos.x - Pos.x));
	Vector2D<T> temp;
	temp.x = cosf(angle * RadToDeg);
	temp.y = sinf(angle * RadToDeg);
	return temp;

}

/// <summary>
/// ����W(origin)����A�w�肵���p�x(angleDeg)�Ƌ���(distance)�ŋ��߂����W��Ԃ��B
/// </summary>
/// <param name="origin">����W</param>
/// <param name="angleDeg">�p�x�i�x���@�j</param>
/// <param name="distance">����</param>
/// <returns>�v�Z��̍��W</returns>
template<typename T>
Vector2D<T> GetPointFromAngle(const Vector2D<T>& center,float distance,float angleDeg) {
	float rad = angleDeg * PI / 180.0f;
	//	
	return { center.x + std::cos(rad) * distance,
			 center.y + std::sin(rad) * distance };
}



//	�G���A�X
using Vector2Df = Vector2D<float>;
using Vector2Di = Vector2D<int>;
