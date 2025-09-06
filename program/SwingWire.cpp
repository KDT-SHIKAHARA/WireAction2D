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

// �A���J�[�ړ�
void SwingWire::MoveAnchor()
{
    anchorPos_ += fireDir_ * fireSpeed_ * Time::deltaTime();

    if ((anchorPos_ - objPos_).GetLength() > maxLength_) {
        isFinish_ = true;
    }
}

// �A���J�[�ڑ�����
void SwingWire::CheckAnchorCollision()
{
    if (MapManager::Instance().CheckPointHit(anchorPos_)) {
        wireLength_ = (anchorPos_ - objPos_).GetLength();
        theta_ = atan2f(objPos_.y - anchorPos_.y, objPos_.x - anchorPos_.x) - (3.1415f / 2.0f);
        omega_ = 0.0f;

        state_ = State::Swinging;

        rigidBody_->isStatic_.Set(true);	//	�d�͒�~
        //rigidBody_->SetVelocity(Vector2D<float>{0, 0});

    }
}

// �U��q�^���v�Z
void SwingWire::CalculateSwing()
{
    //auto dt = Time::deltaTime();
    //// ���͕␳�i���E�L�[�ŐU�������j
    //float inputForce = 0.0f;
    //if (Input::IsKeyOn(KEY_INPUT_A)) inputForce = -kInputForce;
    //if (Input::IsKeyOn(KEY_INPUT_D)) inputForce = kInputForce;
    //// �P�U��q�^��
    //float alpha = -(gravity_ / wireLength_) * sinf(theta_) - damping_ * omega_ + inputForce;
    //omega_ += alpha * dt;
    //theta_ += omega_ * dt;
    //// �V�����ʒu
    //Vector2Df direction = { cosf(theta_ + 3.1415f / 2.0f), sinf(theta_ + 3.1415f / 2.0f) };
    //Vector2Df newPos = anchorPos_ + direction * wireLength_;
    //// ���x�x�N�g���X�V
    //lastVelocity_ = newPos - objPos_;
    //objPos_ = newPos;
    //// ���a�����̑��x�������폜���Ċ����Ƃ��� Rigidbody �ɓn��
    //float radial = lastVelocity_.x * direction.x + lastVelocity_.y * direction.y;
    //Vector2Df tangentialVel = lastVelocity_ - direction * radial;
    //float inrFactor = 1.2f;
    //if (rigidBody_) {
    //    rigidBody_->SetVelocity(tangentialVel * inrFactor);
    //}
    //// transform �ʒu�X�V�i�K�v�ɉ����āj
    //GetGameObj()->transform.SetWorldPosition(objPos_);
    //if (MapManager::Instance().CheckAABB(GetGameObj())) {
    //    isFinish_ = true;
    //    //rigidBody_->SetVelocity({ 0,0 });
    //}



    auto dt = Time::deltaTime();
    if (dt <= 0.f) return;

    // ���͕␳
    float inputForce = 0.0f;
    if (Input::IsKeyOn(KEY_INPUT_A)) inputForce = -kInputForce;
    if (Input::IsKeyOn(KEY_INPUT_D)) inputForce = kInputForce;

    // �P�U��q�^��
    float alpha = -(gravity_ / wireLength_) * sinf(theta_) - damping_ * omega_ + inputForce;
    omega_ += alpha * dt;
    theta_ += omega_ * dt;

    // �ڐ������̐V�����ʒu
    Vector2Df direction = { cosf(theta_ + 3.1415f / 2.0f), sinf(theta_ + 3.1415f / 2.0f) };
    Vector2Df targetPos = anchorPos_ + direction * wireLength_;

    // �O�t���[���̈ʒu�Ƃ̍����ő��x�v�Z
    Vector2Df velocity = (targetPos - objPos_) / dt;

    // Rigidbody �ɑ��x�Z�b�g
    if (rigidBody_) {
        rigidBody_->SetVelocity(velocity);
    }

    // �O�t���[���̈ʒu�Ƃ��ĕێ�
    objPos_ = targetPos;

    // �Փ˔���
    if (MapManager::Instance().CheckAABB(GetGameObj())) {
        isFinish_ = true;
        if (rigidBody_) {
            rigidBody_->AddVelocity(velocity * 0.5f); // �������c��
        }
    }
}




// ���͂Ŕ���
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

// ����
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

// �X�V
void SwingWire::Update()
{
    objPos_ = GetGameObj()->transform.WorldPosition();
    auto playerState = GetGameObj()->GetComponent<StateController>();
    if (!playerState) return;
    playerState->isSpace.Set(false);

    if (playerState->CanSwingWire()) {
        // ���͔���
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

// �`��
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
