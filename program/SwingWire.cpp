#include "swingwire.h"
#include "gameobject.h"
#include "input.h"
#include "camera.h"
#include "collidercomp.h"
#include "time.h"
#include "mapmanager.h"
#include<dxlib.h>
#include <memory>
#include "RigidbodyComp.h"
#include <cmath>
#include"PlayerStateController.h"


// ---------------- Implementation ----------------
void SwingWire::Start() {
    rigidBody_ = GetGameObj()->GetComponent<RigidbodyComp>();
    size_ = GetGameObj()->GetComponent<ColliderComp>()->size();
}

// アンカー移動
void SwingWire::MoveAnchor()
{
    anchorPos_ += fireDir_ * fireSpeed_ * Time::deltaTime();

    if ((anchorPos_ - objPos_).GetLength() > maxLength_) {
        isFinish_ = true;
    }
}

// アンカー接続判定
void SwingWire::CheckAnchorCollision()
{
    if (MapManager::Instance().CheckPointHit(anchorPos_)) {
        wireLength_ = (anchorPos_ - objPos_).GetLength();
        theta_ = atan2f(objPos_.y - anchorPos_.y, objPos_.x - anchorPos_.x) - (3.1415f / 2.0f);
        omega_ = 0.0f;

        state_ = State::Swinging;

        rigidBody_->isStatic_.Set(true);	//	重力停止
        //rigidBody_->SetVelocity(Vector2D<float>{0, 0});

    }
}

// 振り子運動計算
void SwingWire::CalculateSwing()
{
    //auto dt = Time::deltaTime();
    //// 入力補正（左右キーで振幅増減）
    //float inputForce = 0.0f;
    //if (Input::IsKeyOn(KEY_INPUT_A)) inputForce = -kInputForce;
    //if (Input::IsKeyOn(KEY_INPUT_D)) inputForce = kInputForce;
    //// 単振り子運動
    //float alpha = -(gravity_ / wireLength_) * sinf(theta_) - damping_ * omega_ + inputForce;
    //omega_ += alpha * dt;
    //theta_ += omega_ * dt;
    //// 新しい位置
    //Vector2Df direction = { cosf(theta_ + 3.1415f / 2.0f), sinf(theta_ + 3.1415f / 2.0f) };
    //Vector2Df newPos = anchorPos_ + direction * wireLength_;
    //// 速度ベクトル更新
    //lastVelocity_ = newPos - objPos_;
    //objPos_ = newPos;
    //// 半径方向の速度成分を削除して慣性として Rigidbody に渡す
    //float radial = lastVelocity_.x * direction.x + lastVelocity_.y * direction.y;
    //Vector2Df tangentialVel = lastVelocity_ - direction * radial;
    //float inrFactor = 1.2f;
    //if (rigidBody_) {
    //    rigidBody_->SetVelocity(tangentialVel * inrFactor);
    //}
    //// transform 位置更新（必要に応じて）
    //GetGameObj()->transform.SetWorldPosition(objPos_);
    //if (MapManager::Instance().CheckAABB(GetGameObj())) {
    //    isFinish_ = true;
    //    //rigidBody_->SetVelocity({ 0,0 });
    //}



    auto dt = Time::deltaTime();
    if (dt <= 0.f) return;

    // 入力補正
    float inputForce = 0.0f;
    if (Input::IsKeyOn(KEY_INPUT_A)) inputForce = -kInputForce;
    if (Input::IsKeyOn(KEY_INPUT_D)) inputForce = kInputForce;

    // 単振り子運動
    float alpha = -(gravity_ / wireLength_) * sinf(theta_) - damping_ * omega_ + inputForce;
    omega_ += alpha * dt;
    theta_ += omega_ * dt;

    // 接線方向の新しい位置
    Vector2Df direction = { cosf(theta_ + 3.1415f / 2.0f), sinf(theta_ + 3.1415f / 2.0f) };
    Vector2Df targetPos = anchorPos_ + direction * wireLength_;

    // 前フレームの位置との差分で速度計算
    Vector2Df velocity = (targetPos - objPos_) / dt;

    // Rigidbody に速度セット
    if (rigidBody_) {
        rigidBody_->SetVelocity(velocity);
    }

    // 前フレームの位置として保持
    objPos_ = targetPos;

    // 衝突判定
    if (MapManager::Instance().CheckAABB(GetGameObj())) {
        isFinish_ = true;
        if (rigidBody_) {
            rigidBody_->AddVelocity(velocity * 0.5f); // 慣性を残す
        }
    }
}




// 入力で発射
void SwingWire::Fire()
{
    if (state_ != State::Idle) return;
    isFinish_ = false;
    Vector2Df mouseWorld = Camera::Instance().ScreenToWorld(Vector2Df{ (float)Input::MouseX(), (float)Input::MouseY() });
    fireDir_ = mouseWorld - objPos_;
    fireDir_.Normalize();
    anchorPos_ = objPos_;
    state_ = State::Firing;
    lastVelocity_ = rigidBody_->velocityRaw();

}

// 解除
void SwingWire::Release()
{
    state_ = State::Idle;

    if (rigidBody_) {
        float inrFactor = 0.8f;
        lastVelocity_ = rigidBody_->velocityRaw();
        lastVelocity_.y *= inrFactor;
        rigidBody_->SetVelocity(lastVelocity_);
    }

    theta_ = 0.f;
    omega_ = 0.f;
}

// 更新
void SwingWire::Update()
{
    objPos_ = GetGameObj()->transform.WorldPosition();
    auto playerState = GetGameObj()->GetComponent<StateController>();
    if (!playerState) return;
    playerState->isSpace.Set(false);

    if (playerState->CanSwingWire()) {
        // 入力判定
        if (Input::IsMouseOn(MOUSE_INPUT_RIGHT)) {
            Fire();
            playerState->RequestSwingWire();
        }

    }

    switch (state_) {
    case State::Idle:
        break;
    case State::Firing:
        MoveAnchor();
        CheckAnchorCollision();
        break;
    case State::Swinging:
        CalculateSwing();
        if (Input::IsKeyOn(KEY_INPUT_SPACE)) {
            playerState->isSpace.Set(true);
            isFinish_ = true;
        }
        break;
    }
}

// 描画
void SwingWire::Render()
{
    if (state_ == State::Firing || state_ == State::Swinging) {
        const auto& camPos = Camera::Instance().position();
        const auto& camSize = Camera::Instance().area_size();
        auto size = GetGameObj()->GetComponent<ColliderComp>()->size();

        float screenObjX = objPos_.x + (size.x / 2) - camPos.x + camSize.x / 2;
        float screenObjY = objPos_.y + (size.x / 2) - camPos.y + camSize.y / 2;
        float screenAnchorX = anchorPos_.x - camPos.x + camSize.x / 2;
        float screenAnchorY = anchorPos_.y - camPos.y + camSize.y / 2;

        DrawLineAA(screenObjX, screenObjY, screenAnchorX, screenAnchorY, GetColor(0, 0, 255), 2);
    }
}
