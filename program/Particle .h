#pragma once
#include <vector>

/// <summary>
/// ���q�\����
/// </summary>
struct Particle {
    float x, y;       // �ʒu
    float vx, vy;     // ���x
    float life;       // �c����� (0.0�`1.0)
    float size;       // �T�C�Y
    int r, g, b, a;  // �F
};


class ParticleSystem {
public:
    std::vector<Particle> particles;
    int screenWidth;
    int screenHeight;

    ParticleSystem(int w, int h) : screenWidth(w), screenHeight(h) {
        particles.reserve(500); // �ő�500���q
    }

    void SpawnParticle(int num);

    void Update();

    void Render();
};