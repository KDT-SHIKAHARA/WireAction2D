#include "transform.h"
#include<cmath>
#include"DebugLog.h"
#include"GameObject.h"
#include "RigidbodyComp.h"

// ==================================================================
// ファイル名	：transform.h
// 制作日		：2025.7.15
// 更新日		：2025.7.15
// 制作者		：鹿原（shikahara）
// 概要			：座標、回転、スケールの管理や操作をするクラス
// 変更履歴		：なし
// ===================================================================


/// <summary>
/// 親が存在していたら削除して、存在していなかったら追加をする。
/// また循環参照にならないように自分の先祖に親にしたいオブジェクトが存在していないかを判断
/// </summary>
/// <param name="arg_new_parent"> 新しい親のポインタ </param>
void Transform::SetParent(const std::shared_ptr<Transform>& arg_new_parent){
	//	新しい親が自分かどうかの判定＆新しい親が自分の先祖にいたら自分は先祖なので
	//	先祖が親になるのはおかしいので防止用のメソッド
	//	いたら親の設定をしない。循環参照防止
	if (arg_new_parent.get() == this|| IsInAncestorChain(arg_new_parent)) {
		return;
	}

	//　親が存在していたら
	if (const auto& parent_ptr = parent_.lock()) {
		auto& parent_children = parent_ptr->children_;
		parent_children.erase(std::remove(parent_children.begin(), parent_children.end(), shared_from_this()), parent_children.end());
	}

	//	親の変更
	parent_ = arg_new_parent;
	//	親がnullptrじゃなければ
	if (arg_new_parent) {
		arg_new_parent->children_.push_back(shared_from_this());
	}

}



/// <summary>
/// 実際の座標取得
/// </summary>
/// <returns> 実際の座標 </returns>
Vector2D<float> Transform::WorldPosition() const{
	//	親ポインタ取得
	auto parent_ptr = parent();
	//	存在していなかったら座標を返す
	if (!parent_ptr) return position_;
	//	存在していたら親の角度を基準として座標分足す。
	Vector2D<float> scalePosition = (Vector2D<float>)position_ * parent_ptr->WorldScale();
	return parent_ptr->WorldPosition() + (scalePosition.Rotated(parent_ptr->WorldRotation()));
}

/// <summary>
/// 角度の取得
/// </summary>
/// <returns></returns>
float Transform::WorldRotation() const{
	//	親ポインタ取得
	const auto& parent_ptr = parent_.lock();
	//	存在していたら親からrota分足した角度 : 自分の角度
	return parent_ptr ? (parent_ptr->WorldRotation() + rotation_) : rotation_;
}

/// <summary>
/// サイズの倍率
/// </summary>
/// <returns> 親がいれば親の角度 </returns>
Vector2D<float> Transform::WorldScale() const{
	//	親ポインタ取得
	const auto& parent_ptr = parent_.lock();
	//	存在していなければスケールをそのまま返す
	if (!parent_ptr) return scale_;
	//	存在していれば親を親の比率*自分の比率を返す。
	return (parent_ptr->WorldScale() * scale_);
}

/// <summary>
/// 親がいなければ普通に座標をセットする
/// 親がいれば親の移動ベクトルを基準にして、移動させる
/// </summary>
/// <param name="worldPosition"></param>
void Transform::SetWorldPosition(const Vector2D<float>& worldPosition){
	//	親ポインタ取得
	const auto& parent_ptr = parent_.lock();
	//	存在していなければ座標をそのままセット
	if (!parent_ptr) {
		position_ = worldPosition;
		return;
	}

	//	存在していれば
	//	親の位置と角度を基準として空間座標を設定する

	//	差分計算
	Vector2D<float> delta = worldPosition - parent_ptr->WorldPosition();
	//	差分から角度を使って移動ベクトルを作成(親の回転の打消し)
	Vector2D<float> unrot = delta.Rotated(-parent_ptr->WorldRotation());
	
	// 空間座標の設定(親のスケール位置をずらす、比率合わせ)
	position_ = (unrot / parent_ptr->WorldScale());

}

/// <summary>
/// 親がいなければ普通に角度の設定
/// 親がいれば親の角度から自分の角度分減らす(親回転打消し)
/// </summary>
/// <param name="rad"></param>
void Transform::SetWorldRotasion(float rad){
	//	親ポインタ取得
	auto parent_ptr = parent_.lock();

	//	parent_ptr がnullptrかどうか
	//	true: 親から自分の回転分打ち消した角度　false: 角度をそのまま
	rotation_ = parent_ptr ? rad - parent_ptr->WorldRotation() : rad;
}

/// <summary>
/// 親がいなければ普通にスケールの設定
/// 親がいれば親のスケール / 自分のスケールでサイズ
/// </summary>
/// <param name="arg_scale"> 設定したい自分のスケール </param>
void Transform::SetWorldScale(const Vector2D<float>& arg_scale){
	//	親ポインタ取得
	const auto& parent_ptr = parent_.lock();

	//	parent_ptr がnullptrかどうか
	/// true: 親のスケール / 自分のスケールでサイズ false: そのまま変更
	scale_ = parent_ptr ? (arg_scale / parent_ptr->WorldScale()): arg_scale;
}

/// <summary>
/// 向いている方向に移動ベクトルを作成　
/// </summary>
/// <returns> 方向ベクトル </returns>
Vector2D<float> Transform::Forward() const{
	return { std::cosf(WorldRotation()),std::sinf(WorldRotation()) };
}

/// <summary>
/// 渡された座標に対しての角度を計算する
/// </summary>
/// <param name="arg_target"> 対象の座標 </param>
void Transform::LookAt(const Vector2D<float>& arg_target){
	//	移動ベクトル
	Vector2D dir = arg_target - WorldPosition();
	//	角度
	float angle = std::atan2f(dir.y, dir.x);
	//	セット
	SetWorldRotasion(angle);
}

/// <summary>
/// 指定座標へ移動距離分移動する。
/// 距離より短かったら対象の座標にする。
/// </summary>
/// <param name="target"> 指定座標 </param>
/// <param name="arg_speed"> 移動速度 </param>
void Transform::MoveToTarget(const Vector2D<float>& target, float arg_speed){
	//	移動ベクトル作成
	Vector2D<float> dir = target - WorldPosition();
	//	距離取得
	float length = dir.GetLength();

	//	距離と移動速度の判定
	
	//	距離 < 移動速度 なら指定座標にする
	if (length <= arg_speed) {
		SetWorldPosition(target);
		return;
	}

	//	違うなら正規化をして移動速度分かける
	SetWorldPosition(WorldPosition() + (dir.Normalize() * arg_speed));

}

/// <summary>
/// 向いている方向に移動する。
/// 向きのセットなどはこのメソッドを呼び出す前にセットする。
/// ずっと追跡させるならターゲットセットのメソッドを常に呼び出す
/// </summary>
/// <param name="arg_speed"> 移動速度 </param>
void Transform::MoveToForward(float arg_speed){
	//	向きから方向ベクトルを作成
	Vector2D<float> rot_vector = Forward();

	//	現在座標に移動ベクトルを足す
	SetWorldPosition(WorldPosition() + rot_vector * arg_speed);
}

/// <summary>
/// デバックログに座標と角度とスケールを表示する
/// </summary>
/// <param name="label"></param>
void Transform::AddDebugLog(const std::string& label) const{
	DebugLog::AddDubug(label + " position.x:", position_.x);
	DebugLog::AddDubug(label + " position.y:", position_.y);
	DebugLog::AddDubug(label + " rotation:", rotation_);
	DebugLog::AddDubug(label + " scale.x:", scale_.x);
	DebugLog::AddDubug(label + " scale.y:", scale_.y);
	DebugLog::AddDubug(label + " HasParent:", HasParent());
}

//	向きを取得
Direction Transform::GetAngleType()
{

	// 角度を -π ～ π の範囲に正規化
	while (rotation_ <= -PI) rotation_ += 2 * PI;
	while (rotation_ > PI) rotation_ -= 2 * PI;

	if (rotation_ > -PI / 4 && rotation_ <= PI / 4) {
		return Direction::Right;
	}
	else if (rotation_ > PI / 4 && rotation_ <= 3 * PI / 4) {
		return Direction::Up;
	}
	else if (rotation_ <= -PI / 4 && rotation_ > -3 * PI / 4) {
		return Direction::Down;
	}
	else {
		// 残りは左方向（3π/4 ? π または -π ? -3π/4）
		return Direction::Left;
	}
}




