#pragma once
#include"dxlib.h"

#define BLACK		GetColor(0, 0, 0)
#define WHITE		GetColor(255, 255, 255)
#define GRAY		GetColor(128,128,128)
#define GREEN		GetColor(60, 179, 113)
#define BLUE		GetColor(0, 0, 255)
#define YELLOW		GetColor(255, 255, 0)
#define PINK		GetColor(255, 0, 255)
#define SKYBLUE		GetColor(0, 255, 255)
#define RED			GetColor(255,0,0)
#define PURPLE		GetColor(167,87,168)
#define MOCCASIN	GetColor(255,228,181)
#define SILVER		GetColor(192,192,192)
#define ASHGRAY		GetColor(148,148,148)
#define DARKORANGE	GetColor(255,140,0)
#define	GOLD		GetColor(255,215,0)

// HSV Å® RGB ïœä∑
// h : êFëä (0Å`360)
// s : ç ìx (0Å`1)
// v : ñæìx (0Å`1)
// èoóÕ: r,g,b (0Å`255)
inline void HSVtoRGB(float h, float s, float v, int& r, int& g, int& b)
{
    int i = (int)(h / 60.0f) % 6;
    float f = h / 60.0f - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    float rr, gg, bb;
    switch (i) {
    case 0: rr = v; gg = t; bb = p; break;
    case 1: rr = q; gg = v; bb = p; break;
    case 2: rr = p; gg = v; bb = t; break;
    case 3: rr = p; gg = q; bb = v; break;
    case 4: rr = t; gg = p; bb = v; break;
    case 5: rr = v; gg = p; bb = q; break;
    }

    r = (int)(rr * 255);
    g = (int)(gg * 255);
    b = (int)(bb * 255);
}