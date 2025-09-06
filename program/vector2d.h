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


	// Dot積を計算するメソッド（引数必須）
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

	//	回転
	Vector2D Rotated(const float& radians) {
		float cosR = std::cos(radians);
		float sinR = std::sin(radians);
		//	計算式
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
///	二点の座標と三角関数を使って１フレームごとの移動量を返す関数
/// </summary>
/// <typeparam name="T">		座標系で使っている型(float or int)　</typeparam>
/// <param name="Pos">			移動する側の座標					</param>
/// <param name="TargetPos">	移動されるが他の座標				</param>
/// <returns>					移動量								</returns>
template<typename T>
Vector2D<T> SetTarget(const Vector2D<T>& Pos,const Vector2D<T>& TargetPos) {
	float angle = atan2f((TargetPos.y - Pos.y), (TargetPos.x - Pos.x));
	Vector2D<T> temp;
	temp.x = cosf(angle * RadToDeg);
	temp.y = sinf(angle * RadToDeg);
	return temp;

}

/// <summary>
/// 基準座標(origin)から、指定した角度(angleDeg)と距離(distance)で求めた座標を返す。
/// </summary>
/// <param name="origin">基準座標</param>
/// <param name="angleDeg">角度（度数法）</param>
/// <param name="distance">距離</param>
/// <returns>計算後の座標</returns>
template<typename T>
Vector2D<T> GetPointFromAngle(const Vector2D<T>& center,float distance,float angleDeg) {
	float rad = angleDeg * PI / 180.0f;
	//	
	return { center.x + std::cos(rad) * distance,
			 center.y + std::sin(rad) * distance };
}



//	エリアス
using Vector2Df = Vector2D<float>;
using Vector2Di = Vector2D<int>;
