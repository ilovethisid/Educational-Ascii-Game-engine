/*
    FPS for Windows Based system.
*/
#pragma once

#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "CoordinateSystem.h"
#include "GraphicEngine.h"
#include "Object.h"
#include "KeyListener.hpp"
#include "KeyMacro.hpp"

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;


class GameLoop {

private:
    double fps_;
    Console console_;
    KeyListener key_listener_;
    std::thread* temp_;
    void vGotoXY(Point _point);
    void vHideConsoleCursor();
    DWORD vGetUnitTime();

public:
    GameLoop();
    Console getConsole();
    void setFPS(double frames);
    void BuildScreen(int width, int height, int fontw, int fonth);
    void UpdateScreen();
    void MoveTargetObject(Point target_obj);
};