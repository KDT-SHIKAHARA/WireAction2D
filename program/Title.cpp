#include "Title.h"
#include "dxlib.h"
#include "TextureResourceMng.h"
#include "SystemConfig.h"
#include"GetColor.h"
#include "vector2d.h"
#include "input.h"
#include "debugDef.h"
#include "GameManager.h"
#include "TutorialScene.h"
#include "BossScene.h"
#include "InGameScene.h"

void SCTitle::DrawStr()
{
    // グロー効果: 複数回描画して光を広げる
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50); // 半透明

    float str_x = WINDOW_W / 2;
    float str_y = WINDOW_H / 2 - 70;
    float str_rate = 0.3;
    for (int i = 1; i <= 5; i++) {
        float scale = str_rate + i * 0.002f; // 少し大きめに
        DrawRotaGraphF(
            (float)str_x, (float)str_y,
            scale, 0.0f, str_->GetHandle(), TRUE
        );
    }
    // 中心画像（通常）
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawRotaGraph(str_x, str_y, str_rate, 0, str_->GetHandle(), true);
}

/// <summary>
/// メニューの選択処理
/// </summary>
void SCTitle::MenuSelect()
{
    //  とりあえず未選択に
    select_num_ = NONE;


    for (int i = 0; i < menus_.size(); i++) {
        if (menus_[i]->ChecKMouseHit()) {
            select_num_ = i;
        }
    }

    //  何かを選択している時に
    if (select_num_ < MAX) {
        //  入力判定されていたら
        if (isInput()) {
            //  選択番号に応じて処理を分岐する
            switch (select_num_)
            {
            case START:
                //  スクリーンのポインタ変更をする
                GameManager::Instance().CreateScene<InGameScene>();
                break;
            case BOSSDEBUG:
                GameManager::Instance().CreateScene<BossStage>();
                break;

            }
        }
    }

}

/// <summary>
/// メニュー関連の描画
/// </summary>
void SCTitle::MenuDraw()
{    

    SetFontSize(32);
    for (int i = 0; i < menus_.size(); i++) {
        menus_[i]->Draw(MOCCASIN);
        if (i == select_num_) {
            const auto& pos = menus_[i]->Position();
            const auto& size = menus_[i]->Size();
            static int Thickness = 2.0f;
            DrawLine(pos.x, pos.y, pos.x, pos.y + size.y, DARKORANGE, Thickness);
            DrawLine(pos.x + size.x, pos.y, pos.x + size.x, pos.y + size.y, DARKORANGE, Thickness);
        }
    }
    SetFontSize(16);
}

/// <summary>
/// 決定キーが押されているかどうか
/// </summary>
/// <returns></returns>
bool SCTitle::isInput() {
    return Input::IsKeyOn(KEY_INPUT_RETURN) || Input::IsMouseOn(MOUSE_INPUT_LEFT);
}

/// <summary>
/// 初期化
/// </summary>
SCTitle::SCTitle(){
	bg_ = _TEX_RES_MGR(res_bg_);
	str_ = _TEX_RES_MGR(res_str_);
	particles_ = std::make_shared<ParticleSystem>(WINDOW_W,WINDOW_H);


    menus_.push_back(std::make_shared<BoxButton>(
        Vector2Df{ (float)WINDOW_W / 2, (float)WINDOW_H / 2 + 150 }, Vector2Df{ 200,80 }, "Start"));

#ifdef _DEBUG
    menus_.push_back(std::make_shared<BoxButton>(
        Vector2Df{ (float)WINDOW_W / 2, (float)WINDOW_H / 2 + 250 }, Vector2Df{ 200,80 }, "Boss"));
#endif // _DEBUG


}

void SCTitle::Update()
{
	particles_->SpawnParticle(1);
	particles_->Update();
    MenuSelect();
}

void SCTitle::Render(){
	DrawGraph(0, 0, bg_->GetHandle(), false);
	particles_->Render();
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50); // 半透明
    DrawBox(0, 0, WINDOW_W, WINDOW_H, WHITE, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawStr();
    MenuDraw();


    DEBUG_LOG("title scene");

}
