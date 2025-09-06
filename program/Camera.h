#pragma once
#include"vector2d.h"
#include "flag.h"

//	いつしか存在しないオブジェクトなので今回はメモリ効率より
//	今後の拡張性とバクの起こりずらさを重視
//	分離構造にしてもしカメラがプレイやに遅れて移動するなどの構造を追加するときに
//	あとからしやすいようにと画面範囲の制御を入れやすくする


enum class CameraMode {
	Follow,	//	追従
	Fixed,	//	固定
	Script,	//	外部制御
	None,	//	何もしない
};

class Camera {
	Camera();
	virtual ~Camera() = default;

	void ClampPosToMap();

public:
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	static Camera& Instance() {
		static Camera instance;
		return instance;
	}

	Vector2D<float> position()const { return position_; }
	Vector2D<float> area_size()const { return area_size_; }

	//	モード設定
	void SetMode(CameraMode mode) { mode_ = mode; }

	//	各モード用設定
	void SetFollowPos(const Vector2D<float>& follow) { follow_position_ = follow; }
	void SetFixedPos(const Vector2D<float>& fixed) { fixed_position_ = fixed; }
	void SetScriptPos(const Vector2D<float>& script) { script_position_ = script; }

	void SetFollowSpeed(float follow_speed) { follow_speed_ = follow_speed; }

	Flag isTargetCam_ = true;	//	カメラの追従フラグ	true: 追従する false: 追従しない 

	//	更新
	void Update();

	//	カメラ座標を設定する
	void SetPosition(const Vector2D<float>& position) { position_ = position; }

	Vector2Df ScreenToWorld(const Vector2Df& a_screenPos) {
		// カメラの位置 (スクリーン中央基準)
		Vector2Df cameraPos = position_;  // カメラの位置 (カメラ座標系)

		// 画面の中心 (スクリーン中央)
		Vector2Df screenCenter = Vector2Df(area_size_.x / 2, area_size_.y / 2);

		// スクリーン座標 -> カメラ中心基準座標
		Vector2Df localPos = a_screenPos - screenCenter;

		// カメラの位置を加えてワールド座標に変換
		return localPos + cameraPos;

	};

	//	画面内の判定
private:
	//	カメラ座標、表示範囲
	Vector2D<float> position_;				//	カメラの座標
	Vector2D<float> area_size_;				//	表示するサイズ

	//	モード用データ　
	Vector2D<float> follow_position_;		//	追従するオブジェクト座標
	Vector2D<float> fixed_position_;		//	固定座標
	Vector2D<float> script_position_;		//	スクリプト制御座標

	//	状態
	CameraMode mode_ = CameraMode::Follow;	//	カメラのモード

	//	速度
	float follow_speed_ = 5.0f;				//	カメラの移動速度



};

void DrawRotaGraphCam(const Vector2D<float>& pos, float exRate, float angle, int GrHandle, int TransFlag, int ReverseFlagX, int ReverseFlagY);