#include "StandingBot.h"
#include "RigidbodyComp.h"
#include "ColliderComp.h"
#include "health.h"
#include "HitBOxRenderComp.h"
#include "tag.h"
#include "StandingBotRender.h"

std::shared_ptr<GameObject> StandBot::Create()
{
    std::shared_ptr<GameObject> gameObj = std::make_shared<GameObject>();
    gameObj->AddComponent<RigidbodyComp>();
    gameObj->AddComponent<ColliderComp>();
    gameObj->AddComponent<Health>(1);   //  �����̗͂͒�߂�
    gameObj->AddComponent<HitBoxRenderComp>();
    gameObj->AddComponent<StandBotRender>();
    //  �������W�ݒ�
    gameObj->SetTag(Tag::GetString(TagType::Enemy));
    return std::shared_ptr<GameObject>();
}
