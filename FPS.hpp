/*
    FPS for Windows Based system.
*/
#pragma once

#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "CoordinateSystem.h"
#include "GraphicEngine.h"

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;


class FramePerSecond {

private:
    double mvFPS;
    Console mvConsole;
    void vGotoXY(Point _point);
    void vHideConsoleCursor();
    DWORD vGetUnitTime();

public:
    FramePerSecond();
    Console getConsole();
    void setFPS(double frames);
    void BuildScreen(int width, int height, int fontw, int fonth);
    void UpdateScreen();
    void MoveTargetObject(Point target_obj);
};