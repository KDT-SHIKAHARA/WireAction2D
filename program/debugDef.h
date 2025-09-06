#pragma once
#include"DxLib.h"

#define DEBUG_LEVEL 1

#ifndef NDEBUG
#ifndef Debug 
#define Debug DEBUG_LEVEL
#endif // !Debug 
#endif // !NDEBUG

#ifndef Debug 
#define Debug 0
#endif // !Debug 



#if Debug >= 1 
#define DEBUG_LOG(mes) DrawString(0,20,mes,GetColor(255,0,0));
#else 
#define DEBUG_LOG(mes) 
#endif // Debug >= 1 

#if Debug >= 2 
#define DEBUG_VALUE_LOG(posX,posY,Color,FormatStr,...) DrawFormatString(posX,posY,Color,FormatStr,__VA_ARGS__);
#else 
#define DEBUG_VALUE_LOG(posX,posY,Color,FormatStr,...) 
#endif // Debug >= 2 



