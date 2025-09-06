#include "Particle .h"
#include "Time.h"
#include "dxlib.h"

void ParticleSystem::SpawnParticle(int num)
{
    for (int i = 0; i < num;i++) {
        Particle p;
        p.x = static_cast<float>(rand() % screenWidth);
        p.y = static_cast<float>(screenHeight); // ��ʉ�
        p.vx = 0.0f;
        p.vy = -50.0f - static_cast<float>(rand() % 50); // �����
        p.life = 1.0f;
        p.size = 2.0f + static_cast<float>(rand() % 4);

        // �F�𔒁`�`�I�����W�̃����_��
        int colorType = rand() % 3;
        switch (colorType) {
        case 0: p.r = 255; p.g = 255; p.b = 255; break;       // ��
        case 1: p.r = 100; p.g = 200; p.b = 255; break;       // ��
        case 2: p.r = 255; p.g = 150 + rand() % 106; p.b = 0; break; // �I�����W
        }
        p.a = 255;

        particles.push_back(p);
    }
}


void ParticleSystem::Update() {

    auto dt = Time::deltaTime();
    for (size_t i = 0; i < particles.size(); ) {
        Particle& p = particles[i];
        p.x += p.vx * dt;
        p.y += p.vy * dt;
        p.life -= dt * 0.1f; // ���X�Ɏ�������
        p.a = static_cast<int>(p.life * 255);

        if (p.life <= 0.0f || p.y < 0) {
            // ���������q���폜
            particles[i] = particles.back();
            particles.pop_back();
        }
        else {
            i++;
        }
    }
}


void ParticleSystem::Render() {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
    for (auto& p : particles) {
        // ���̃O���f�[�V�������`��
        int alpha = static_cast<int>(p.life * 255);
        for (int r = static_cast<int>(p.size); r > 0; r--) {
            int a = static_cast<int>(alpha * (float)r / p.size);
            DrawCircleAA(static_cast<int>(p.x), static_cast<int>(p.y), static_cast<float>(r),
                50, GetColor(p.r, p.g, p.b), TRUE, a);
        }
    }
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
