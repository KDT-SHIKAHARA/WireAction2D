#pragma once
#include"DebugScene.h"
//	0: DebugStage
//	1: Title
//	2: Tutorial
//	3: Stage


#ifndef STAGE_DEBUG
#define STAGE_DEBUG 0
#endif // !STAGE_DEBUG

#if STAGE_DEBUG == 1
#define STAGE 
#endif // STAGE_DEBUG == 1

#ifndef STAGE
#define STAGE SceneDebug
#endif // !STAGE
