﻿#pragma once
#include "Ball.h"
//---------------------------------------------------------------------------------------
enum EBrick_Type 
{
    EBT_None,

    EBT_Red,
    EBT_Blue,
    EBT_Unbreakable,
    EBT_Multihit_1,
    EBT_Multihit_2,
    EBT_Multihit_3,
    EBT_Multihit_4,
    EBT_Parachute,
    EBT_Teleport,
    EBT_Ad,
    EBT_Invisible
};

//---------------------------------------------------------------------------------------
enum EDirection_Type
{
    EDT_Left,
    EDT_Up,
    EDT_Right,
    EDT_Down
};

//---------------------------------------------------------------------------------------


class AGraphics_Object
{
public:
    virtual ~AGraphics_Object();
    virtual void Act() = 0;
    virtual void Draw(HDC hdc, RECT& paint_area) = 0;
    virtual void Clear(HDC hdc, RECT& paint_area) = 0;
    virtual bool Is_Finished() = 0;
};


//---------------------------------------------------------------------------------------
class AActive_Brick : public AGraphics_Object
{  
public:
    void Get_Level_Pos(int &dest_brick_x, int &dest_brick_y);
protected:
    AActive_Brick(EBrick_Type brick_type, int level_x, int level_y);
    virtual void Clear(HDC hdc, RECT& paint_area);
    virtual ~AActive_Brick();
    double Get_Brick_X_Pos(bool of_center);
    double Get_Brick_Y_Pos(bool of_center);
    EBrick_Type Brick_Type;
    int Level_X, Level_Y;
    RECT Brick_Rect;
};




//---------------------------------------------------------------------------------------
class AActive_Brick_Red_Blue : public AActive_Brick
{
public:
    AActive_Brick_Red_Blue(EBrick_Type brick_type, int level_x, int level_y);
    ~AActive_Brick_Red_Blue();
    virtual void Act();
    virtual void Draw(HDC hdc, RECT& paint_area);
    virtual bool Is_Finished();
    static void Setup_Colors();
    static void Draw_In_Level(HDC hdc,RECT &brick_rect, EBrick_Type brick_type);
private:
    
 
    int Fade_Step;

    static unsigned char Get_Fading_Channel(unsigned char color, unsigned char bg_color, int step);
    static void Get_Fading_Color(const AColor& origin_color, int step, AColor& result_color);
    static const int Max_Fade_Step = AsConfig::FPS;

    static AColor Fading_Red_Brick_Colors[Max_Fade_Step];
    static AColor Fading_Blue_Brick_Colors[Max_Fade_Step];
};


//---------------------------------------------------------------------------------------
class AActive_Brick_Unbreakable : public AActive_Brick
{
public:
    AActive_Brick_Unbreakable(int level_x, int level_y);
    ~AActive_Brick_Unbreakable();
    virtual void Act();
    virtual void Draw(HDC hdc, RECT& paint_area);
    virtual bool Is_Finished();
    static void Draw_In_Level(HDC hdc, RECT& brick_rect);

private:


    int Animation_Step;
    HRGN Region;
    
    static const int Max_Animation_Step = 12;

};

//---------------------------------------------------------------------------------------
class AActive_Brick_Multihit : public AActive_Brick
{
public:
    AActive_Brick_Multihit(int level_x, int level_y);
    ~AActive_Brick_Multihit();
    virtual void Act();
    virtual void Draw(HDC hdc, RECT& paint_area);
    
    virtual bool Is_Finished();
    static void Draw_In_Level(HDC hdc, RECT& brick_rect, EBrick_Type brick_type);

private:
    static void Draw_Stage(HDC hdc, RECT& brick_rect, int x, int width);
    int Rotation_Step;
    static const int Steps_Per_Turn = 16;
    static const int Max_Rotation_Step = Steps_Per_Turn * 4;

};
//---------------------------------------------------------------------------------------
enum ETeleport_State 
{
    ETS_Starting,
    ETS_Finishing,
    ETS_Done
};
//---------------------------------------------------------------------------------------
class AActive_Brick_Teleport : public AActive_Brick
{
public:
    AActive_Brick_Teleport(int level_x, int level_y, ABall* ball, AActive_Brick_Teleport* destination_teleport);
    ~AActive_Brick_Teleport();
    virtual void Act();
    virtual void Draw(HDC hdc, RECT& paint_area);

    virtual bool Is_Finished();
   
    static void Draw_In_Level(HDC hdc, RECT& brick_rect, int step = 0);
    EDirection_Type Release_Direction;
private:
    void Set_Ball(ABall* ball);
    ETeleport_State Teleport_State;
    ABall* Ball;
    AActive_Brick_Teleport *Destination_Teleport;
    int Animation_Step;
    static const int Max_Animation_Step = 12;

};

//---------------------------------------------------------------------------------------
class AAdvertisement : public AGraphics_Object
{
public:
    AAdvertisement(int level_x, int level_y, int width, int height);
    ~AAdvertisement();
    virtual void Act();
    virtual void Draw(HDC hdc, RECT& paint_area);
    virtual void Clear(HDC hdc, RECT& paint_area);
    virtual bool Is_Finished();
    void Show_Under_Brick(int level_x, int level_y);
    bool Has_Brick_At(int level_x, int level_y);
private:
    int Level_X, Level_Y, Width, Height;
    RECT Ad_Rect;
    HRGN *Brick_Regions;
    static const int Ball_Size = 12;
    static const int High_Ball_Treshold = 12 * AsConfig::Global_Scale;
    static const int Low_Ball_Treshold = -3 * AsConfig::Global_Scale;
    static const int Deformation_Height = 2 * AsConfig::Global_Scale;
    int Ball_Y_Offset;
    double Falling_Speed, Acceleration_Step, Deformation_Ratio;

    int Ball_X, Ball_Y;
    int Ball_Width, Ball_Height;
    HRGN Empty_Region;
};
//---------------------------------------------------------------------------------------
class AActive_Brick_Ad : public AActive_Brick
{
public:
    AActive_Brick_Ad(int level_x, int level_y, AAdvertisement* advertisement);
    ~AActive_Brick_Ad();
    virtual void Act();
    virtual void Draw(HDC hdc, RECT& paint_area);
    virtual bool Is_Finished();
    static void Draw_In_Level(HDC hdc, RECT& brick_rect);

private:
    AAdvertisement* Advertisement;
    static const int Circle_Size = 7;

};