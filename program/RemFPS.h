//=============================================================
//
//	RemFPS
//
//=============================================================

//=============================================================
//
// 2019/11/17	18:56:00	Ver.1.02	Add Print Pos
// 2019/11/14	15:48:00	Ver.1.01	Miner Fix
// 2019/11/08	00:00:00	Ver.1.00	Test
//=============================================================

#pragma once
//-------------------------------------------------------------
#include "DxLib.h"

//=============================================================
// class
//=============================================================
class CRemFPS {
	int m_nStartTime;	// StartTime
	int m_nCount;		// Count
	float m_fFps;		// FPS
	int N = 60;
	int FPS = 60;
	int m_nX = 0, m_nY = 0;

public:
	// Constructor
	CRemFPS(int x = 0, int y = 0, int fps = 60) {
		// Reset
		m_nStartTime = 0;
		m_nCount = 0;
		m_fFps = 0;
		N = FPS = fps;
		m_nX = x, m_nY = y;
	}

	// Update
	void Update() {
		if (m_nCount == 0) {
			m_nStartTime = GetNowCount();
		}
		if (m_nCount == N) {
			int t = GetNowCount();
			m_fFps = 1000.f / ((t - m_nStartTime) / (float)N);
			m_nCount = 0;
			m_nStartTime = t;
		}
		m_nCount++;
	}

	// Draw
	void Draw() {
		DrawFormatString(m_nX, m_nY, GetColor(255, 255, 255), "%.2f fps", m_fFps);
	}

	// Wait
	void Wait() {
		int nTookTime = GetNowCount() - m_nStartTime;
		int nWaitTime = m_nCount * 1000 / FPS - nTookTime;
		if (nWaitTime > 0) {
			Sleep(nWaitTime);
		}
	}
};