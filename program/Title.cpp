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
    // �O���[����: ������`�悵�Č����L����
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50); // ������

    float str_x = WINDOW_W / 2;
    float str_y = WINDOW_H / 2 - 70;
    float str_rate = 0.3;
    for (int i = 1; i <= 5; i++) {
        float scale = str_rate + i * 0.002f; // �����傫�߂�
        DrawRotaGraphF(
            (float)str_x, (float)str_y,
            scale, 0.0f, str_->GetHandle(), TRUE
        );
    }
    // ���S�摜�i�ʏ�j
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawRotaGraph(str_x, str_y, str_rate, 0, str_->GetHandle(), true);
}

/// <summary>
/// ���j���[�̑I������
/// </summary>
void SCTitle::MenuSelect()
{
    //  �Ƃ肠�������I����
    select_num_ = NONE;


    for (int i = 0; i < menus_.size(); i++) {
        if (menus_[i]->ChecKMouseHit()) {
            select_num_ = i;
        }
    }

    //  ������I�����Ă��鎞��
    if (select_num_ < MAX) {
        //  ���͔��肳��Ă�����
        if (isInput()) {
            //  �I��ԍ��ɉ����ď����𕪊򂷂�
            switch (select_num_)
            {
            case START:
                //  �X�N���[���̃|�C���^�ύX������
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
/// ���j���[�֘A�̕`��
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
/// ����L�[��������Ă��邩�ǂ���
/// </summary>
/// <returns></returns>
bool SCTitle::isInput() {
    return Input::IsKeyOn(KEY_INPUT_RETURN) || Input::IsMouseOn(MOUSE_INPUT_LEFT);
}

/// <summary>
/// ������
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
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50); // ������
    DrawBox(0, 0, WINDOW_W, WINDOW_H, WHITE, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawStr();
    MenuDraw();


    DEBUG_LOG("title scene");

}
