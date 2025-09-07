#include "ColliderSystem.h"
#include "GameObjectMgr.h"
#include"CheckHit.h"
#include "ColliderEvent.h"
#include "tag.h"

//  組み合わせの追加
ColliderSystem::ColliderSystem() {
    rule_.AddRule(Tag::GetString(TagType::Player), Tag::GetString(TagType::Needle));
    rule_.AddRule(Tag::GetString(TagType::Player), Tag::GetString(TagType::Goal));

}

//  当たり判定そのもの
bool ColliderSystem::checkCollision(std::shared_ptr<GameObject> obj1, std::shared_ptr<ColliderComp> collider1, std::shared_ptr<GameObject> obj2, std::shared_ptr<ColliderComp> collider2)
{
    auto pos1 = obj1->transform.WorldPosition();
    auto pos2 = obj2->transform.WorldPosition();

    auto size1 = std::static_pointer_cast<ColliderComp>(collider1)->size();
    auto size2 = std::static_pointer_cast<ColliderComp>(collider2)->size();

    return CheckHit::BoxBox(pos1, size1, pos2, size2);
}

void ColliderSystem::PushBack(std::shared_ptr<GameObject> object1, std::shared_ptr<ColliderComp> collider1, std::shared_ptr<GameObject> object2, std::shared_ptr<ColliderComp> collider2, bool both)
{
    auto pos1 = object1->transform.WorldPosition();
    auto pos2 = object2->transform.WorldPosition();

    auto size1 = std::static_pointer_cast<ColliderComp>(collider1)->size();
    auto size2 = std::static_pointer_cast<ColliderComp>(collider2)->size();

    float dx = (pos1.x - pos2.x);
    float overlapX = (size1.x / 2 + size2.x / 2) - std::abs(dx);

    float dy = (pos1.y - pos2.y);
    float overlapY = (size1.y / 2 + size2.y / 2) - std::abs(dy);

    if (overlapX < overlapY) {
        float move = both ? overlapX / 2 : overlapX;
        if (dx > 0) pos1.x += move;
        else        pos1.x -= move;
    }
    else {
        float move = both ? overlapY / 2 : overlapY;
        if (dy > 0) pos1.y += move;
        else        pos1.y -= move;
    }

    object1->transform.SetWorldPosition(pos1);
}

void ColliderSystem::Update() {

    //  全てのタグの組み合わせから順に受け取る
    for (const auto& key : rule_.GetAllRules()) {
        auto tags = splitTag(key);
        const auto& tag1 = tags.first;
        const auto& tag2 = tags.second;

        //  タグからオブジェクトのリストを取得する
        auto objList1 = GameObjMgr::Instance().GetGameObjWithTag(tag1);
        auto objList2 = GameObjMgr::Instance().GetGameObjWithTag(tag2);

        //  リスト分コレクションを回す
        for (auto& obj1 : objList1) {
            for(auto& obj2 : objList2){
                //  同じなら次の判定へ
                if (obj1 == obj2) continue;

                //  サイズを持っている当たり判定用のコンポーネントを取得
                auto collider1 = obj1->GetComponent<ColliderComp>();
                auto collider2 = obj2->GetComponent<ColliderComp>();

                //  なければ当たり判定を行わない
                if (!collider1 || !collider2) continue;

                //  当たり判定を行うフラグを確認して折れていたら行わない
                if(!collider1->isActive || !collider2->isActive)continue;

                //  当たり判定
                if (checkCollision(obj1, collider1, obj2, collider2)) {
                    //  押し戻し処理
                    bool push1 = collider1->isPush;
                    bool push2 = collider2->isPush;

                    //  両方の時
                    if (push1 && push2) {
                        PushBack(obj1, collider1, obj2, collider2, true);
                    }
                    //  １だけの時
                    else if (push1) {
                        PushBack(obj1, collider1, obj2, collider2, false);
                    }
                    //  ２だけの時
                    else if (push2) {
                        PushBack(obj2, collider2, obj1, collider1, false);
                    }

                    //  被弾したことを通知させる
                    //  今回は即死なのでプレイヤーに持たせている生存フラグを折る
                    auto playerTag = Tag::GetString(TagType::Player);
                    auto goalTag = Tag::GetString(TagType::Goal);

                    if (tag1 != goalTag && tag2 != goalTag) {
                        if (tag1 == playerTag) {
                            auto end = obj1->GetComponent<ColliderEvent>();
                            if (!end) continue;
                            end->hitDeadly = true;

                        }
                        else if (tag2 == playerTag) {
                            auto end = obj2->GetComponent<ColliderEvent>();
                            if (!end) continue;
                            end->hitDeadly = true;

                        }
                    }
                    else {
                       if (tag1 == playerTag) {
                            auto next = obj2->GetComponent<ColliderEvent>();
                            if (!next)continue;
                            next->hitDeadly = true;
                        }

                        else if (tag2 == playerTag) {
                            auto next = obj1->GetComponent<ColliderEvent>();
                            if (!next) continue;
                            next->hitDeadly = true;

                        }
                    }
                }
            }
        }
    }
}