/*
    FPS for Windows Based system.
*/
#pragma once

#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "CoordinateSystem.h"

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;


class FramePerSecond {
private:

    void gotoxy(Point _point);
    void hideConsoleCursor();

public:
    FramePerSecond();
    void moveTargetObject(Point target_obj);
};