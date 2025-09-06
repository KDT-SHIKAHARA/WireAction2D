#pragma once
#include<memory>
#include<vector>
#include<string>
#include"vector2d.h"


#define _XFORM_CREATE std::shared_ptr<Transform>(std::make_shared<Transform>())

enum class Direction {
	Right,
	Left,
	Up,
	Down,
};

class Transform :public std::enable_shared_from_this<Transform> {
	using Xform = std::shared_ptr<Transform>;	//	自分のshared_ptr
	using Parent = std::weak_ptr<Transform>;	//	親
	using Children = std::vector<std::shared_ptr<Transform>>;	//	子供コレクション

	Vector2D<float> position_;	//	座標
	float rotation_;			//	角度
	Vector2D<float> scale_;		//	スケール
	Parent parent_;				//	親
	Children children_;			//	子供

	Direction angleTupe_ = Direction::Right;

public:	
	Transform() 
		:position_({ 0,0 }), rotation_(0.0f), scale_({ 1.0f,1.0f }){ }

	//	デバック
	static inline float ToDeg(float rad) { return rad * (180.0f / 3.1415926f); }
	static inline float ToRad(float deg) { return deg * (3.1415926f / 180.0f); }

	//	親の先祖に自分がいるかどうかの判定
	bool IsInAncestorChain(const Xform& arg_new_parent) {
		//	参照取得
		auto current = parent_.lock();	
		//	自分の先祖全てを検索
		while (current) {
			//	自分から見て祖先に新しい親がいるなら自分は先祖である
			if (current == arg_new_parent) return true;
			current = current->parent_.lock();
		}
		return false;
	}

	//	親の設定と親側の自分を子供設定
	void SetParent(const std::shared_ptr<Transform>& arg_new_parent);

	//	親の削除
	void ClearParent() { SetParent(nullptr); }

	//	親の存在判定 true: 存在している false: 存在していない
	bool HasParent()const { return  !parent_.expired(); }

	//	親の取得
	Xform parent()const { return parent_.lock(); }

	//	子供の取得
	Children children()const { return children_; }

	//	始祖の取得
	Xform GetRoot() {
		//	先祖である自分のポインタ取得
		auto current = shared_from_this();
		//	自分の親の親を見続けて先祖がいなくなるまで検索
		while (auto parent = current->parent_.lock()) {
			//	見る対象を１つづつ上へ
			current = parent;
		}
		//	一番上の階層のポインタを返す。
		return current;
	}


	//	--------------------------ローカル座標アクセサ--------------------------
	void SetPosition(const Vector2D<float>& arg_position) { position_ = arg_position; }
	Vector2D<float> position()const { return position_; }
	void AddPosition(const Vector2D<float>& arg_position) { position_ += arg_position; }
	void SetRotation(const float& arg_rotation) {rotation_= arg_rotation; }
	float rotation()const { return rotation_; }
	void SetScale(const Vector2D<float>& arg_scale) { scale_ = arg_scale; }
	Vector2D<float> scale()const { return scale_; }



	//	--------------------------グローバル座標アクセサ--------------------------
	//------ 取得------


	//	ワールドでの座標の取得
	//	親がいれば親から自分の数値分ずらす。
	//	親の回転量も考慮する
	Vector2D<float> WorldPosition()const;

	//	ワールドでの回転量も取得
	//	親がいれば親からどれくらい回転させるか
	float WorldRotation()const;

	//	ワールドでのスケール取得
	Vector2D<float> WorldScale()const;


	//	------ セット ------


	//	ワールドでの座標設定
	void SetWorldPosition(const Vector2D<float>& arg_position);

	//	ワールドでのラジアン角設定
	void SetWorldRotasion(float arg_rad);

	//	ワールドでのスケール設定
	void SetWorldScale(const Vector2D<float>& arg_scale);


	// ------ 操作 ------
	void Translate(const Vector2D<float>& arg_delta_vector) { position_ += arg_delta_vector; }
	void Rotate(const float& deltaRad) { rotation_ += deltaRad; }
	void Scale(const Vector2D<float>& arg_scale) { scale_ = scale_ * arg_scale; }

	// ------ 方向ベクトル ------

	//	向いている方向への移動ベクトル
	Vector2D<float> Forward()const;

	//	座標を指定してその方向への角度を計算
	void LookAt(const Vector2D<float>& arg_target);

	//	指定座標へ移動距離分移動する。
	void MoveToTarget(const Vector2D<float>& target, float arg_speed);

	//	向いている方向に移動する。
	void MoveToForward(float arg_speed);

	//	デバックログに追加
	void AddDebugLog(const std::string& label = "")const;


	//	-----方向-----

	//	角度から方向を取得
	Direction GetAngleType();

};
