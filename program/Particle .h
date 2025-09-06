#pragma once
#include <vector>

/// <summary>
/// 粒子構造体
/// </summary>
struct Particle {
    float x, y;       // 位置
    float vx, vy;     // 速度
    float life;       // 残り寿命 (0.0～1.0)
    float size;       // サイズ
    int r, g, b, a;  // 色
};


class ParticleSystem {
public:
    std::vector<Particle> particles;
    int screenWidth;
    int screenHeight;

    ParticleSystem(int w, int h) : screenWidth(w), screenHeight(h) {
        particles.reserve(500); // 最大500粒子
    }

    void SpawnParticle(int num);

    void Update();

    void Render();
};