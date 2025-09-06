#define NOMINMAX

#include "Anim2D.h"
#include<sstream>
#include<fstream>
#include<cassert>
#include<algorithm>

#include"TextureResourceMng.h"
#include"Time.h"

/// <summary>
/// フレームを次に進める
/// 終点に達した場合、終了をするのかまたループするのかを判定して処理を分岐差せる
/// </summary>
void Anim2D::stepFrame()
{
	if (frames_.empty()) return;

	switch (mode_) {
	case PlayMode::Loop:
		current_ = (current_ + 1) % frames_.size();
		break;

	case PlayMode::Ones:
		if (current_ + 1 >= frames_.size()) {
			isPlaying_ = false;
			isFinished_ = true;
		}
		else {
			current_++;
		}
		break;
	}
}

/// <summary>
/// 連番の画像を読み込んでフレーム構造体を作成する
/// </summary>
/// <param name="path"></param>
/// <param name="num_frames"></param>
/// <param name="duration"></param>
void Anim2D::LoadFrames(const std::string& path, int num_frames, float duration, float exRate, PlayMode playMode)
{
	for (int i = 0; i < num_frames; i++) {
		std::string filepath = path + std::to_string(i) + ".png";
		auto texture = TextureResourceMgr::Instance().GetTexture(filepath);
		assert(texture->GetHandle() != -1);
		frames_.push_back(texture);
	}
	duration_ms_ = duration;
	current_ = 0;
	elapsed_ms_ = 0.0;
	isPlaying_ = true;
	draw_scale_ = exRate;
	mode_ = playMode;

}



//	描画率の設定
void Anim2D::SetDrawScale(float scale)
{
	scale = std::max(0.01f, scale);
	draw_scale_ = scale;
}

/// <summary>
/// animationの切り替え処理など
/// </summary>
void Anim2D::Update() {
	if (!isPlaying_ || frames_.empty()) return;


	elapsed_ms_ += Time::deltaTime();
	//	越していたらその分フレームを進める
	//	フレーム割れをしたときように越している分全て進める
	while (elapsed_ms_ >= duration_ms_) {
		elapsed_ms_ -= duration_ms_;	//	時間を減らす
		stepFrame();//	フレームを進める
		if (!isPlaying_) break;	//	経過時間の関係で次まで行ってしまったときに終了できるように
	}

}

void Anim2D::Render(float x, float y)
{
	if (frames_.empty())return;
	DrawRotaGraphF(x, y, draw_scale_, rotation_rad_, frames_[current_]->GetHandle(), TRUE, isFlip_);
}
