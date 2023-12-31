﻿#pragma once
#include <Windows.h>
#include "Border.h"
#include "Level.h"
#include "Platform.h"
//---------------------------------------------------------------------------------------

enum EKey_Type {
    EKT_Left,
    EKT_Right,
    EKT_Space
};


enum EGame_State {
    EGS_Test_Ball,

    EGS_Play_Level,
    EGS_Lost_Ball,
    EGS_Restart_Level
};

//---------------------------------------------------------------------------------------
const int Timer_ID = WM_USER + 1;

class AsEngine {
public:
    AsEngine();
    void Init_Engine(HWND hWnd);
    void Draw_Frame(HDC hdc, RECT &paint_area);
    int On_Key(EKey_Type key_type, bool key_down);
    int On_Timer();
   
    
    
private:
    void Play_Level();
    void Restart_Level();
    void Act();
    void On_Falling_Letter(AFalling_Letter* falling_letter);
    EGame_State Game_State;
    //ABall Ball;
    ABall Balls[AsConfig::Max_Balls_Count];
    AsLevel Level;
    AsPlatform Platform;
    AsBorder Border;
};
