#pragma once
#include<memory>
#include<vector>
#include<string>


#include"TextureResource.h"
#include"flag.h"

/// <summary>
/// 複数の画像でアニメーションを行う
/// componentにすると管理面倒なのでこれのインスタンスを管理するcomponentをそのGameObject毎に作る方針にします。
/// 2025.8.13
/// 
/// @ アニメーションに必要な画像ハンドルの管理
/// @ フレームの切り替え時間
/// @ 再生状態の設定とそれに応じた再生処理
/// @ 
/// </summary>
class Anim2D {

	//	フレームを進める
	void stepFrame();

public:
	//	再生モード
	enum class PlayMode {
		Loop,		//	0-1-2-0-1-2... でループ
		Ones,		//	0-1-2 で停止
	};

	//-----ロード系-----
	void LoadFrames(const std::string& path, int num_frames, float duration = 0.2f,float exRate = 1.0f, PlayMode playMode = PlayMode::Loop);

	//-----------------
	//	再生制御
	void Play() { isPlaying_ = true; }
	void Pause() { isPlaying_ = false; }
	void Stop() { isPlaying_ = false;  current_ = 0; }
	void SetPlayMode(PlayMode mode) { mode_ = mode; }
	void SetDrawScale(float scale);
	void SetRotation(float rad) { rotation_rad_ = rad; }
	void Reset() {
		current_ = 0;
		elapsed_ms_ = 0;
		isFinished_ = false;
 		isPlaying_ = true;
	}

	void Update();
	void Render(float x,float y);
private:
	std::vector< std::shared_ptr<TextureResource>> frames_;	//	描画する画像リスト

	//	再生制御
	double elapsed_ms_ = 0;				//	現在のフレームの経過時間
	float duration_ms_ = 0.2f;			//	フレームを切り替える時間
	int current_ = 0;					//	現在再生中のフレーム番号
	PlayMode mode_ = PlayMode::Loop;	//	再生モード

	//	描画パラメーター
	float draw_scale_ = 1.0f;	//	縮小率
	float rotation_rad_ = 0.f;	//	表示の回転


	Flag isPlaying_ = false;		//	再生フラグ
	Flag isFinished_ = false;		//	一回きりの処理が終わったのか

public:
	Flag isFlip_ = false;		//	反転させるかどうか

};