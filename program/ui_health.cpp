#include "ui_health.h"
#include "dxlib.h"
#include "health.h"
#include "GetColor.h"



//	四角形を3重に重ねる
//	1. 色付きの透過率を変更した四角形
//	2. 黒色のないことを示す四角形
//	3. 色付きの本体の四角形
void UiPlayerHp::Box(int num)
{
	//	表示する座標
	auto startX = base_pos_x_ + 40;
	//	左端からサイズ*個数分ずらして、その位置から間隔をずらす
	auto drawX = startX + num * (size_x_ + 10); // 描画するX座標

	//	ずらす座標
	auto gap = 2;
	//	さらにずらす
	auto gap2 = gap * 2;


	//	表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(drawX, base_pos_y_ + gapY_, drawX + size_x_, base_pos_y_ + size_y_ - gapY_, SKYBLUE, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(drawX - gap, base_pos_y_ + gapY_ +  gap, drawX + size_x_ -  gap, base_pos_y_ + size_y_ - gapY_ +  gap, BLACK, TRUE);
	DrawBox(drawX - gap2, base_pos_y_ + gapY_ + gap2, drawX + size_x_ - gap2, base_pos_y_ + size_y_ - gapY_ + gap2, SKYBLUE, TRUE);


}

void UiPlayerHp::Update()
{
	//	存在判定
	if (!healsh_)return;

	//	体力クラスの残りの体力を見て、何ゲージ用意するか
	hp_ = healsh_->Current();

}

void UiPlayerHp::Render()
{

	//	透過率を変更してベースになる四角形を表示する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(base_pos_x_, base_pos_y_, base_pos_x_ + base_size_x_, base_pos_y_ + base_size_y_, BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//	光っているようにブレンド変更

	//	ゲージを用意して。表示する
	for (int i = 0; i < hp_; i++) {
		Box(i);
	}

	//	ブレンドを戻す
}
