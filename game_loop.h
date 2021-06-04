/*
    FPS for Windows Based system.
*/
#pragma once

#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "./Physics/CoordinateSystem.h"
#include "./Physics/Object.h"
#include "./Graphic/GraphicEngine.h"
#include "./KeyListener/KeyListener.hpp"
#include "./KeyListener/KeyMacro.hpp"
#include "./Sound/sound.h"

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;


class GameLoop {

private:
    double fps_;
    boolean is_pause_;
    boolean is_gameover_;
   
    KeyListener key_listener_;
  //  std::thread* temp_;
    clock_t start_, end_, remaining_time_;
    void vHideConsoleCursor();
    DWORD vGetUnitTime();
    void vPrintInfo();

public:
    Console console_;
    vector<Object*> objects;
    gameloop_t keythread;
    GameLoop();
    Console getConsole();

    void initialize();
    void setFPS(double frames);

    void start();
    void update();
    void pause();
    void resume();
    void exitLoop();
    void checkMove(Object& obj);
    void checkResume();


    void checkKey(vector<Object*>& objects);
    void checkShoot(vector<Object*>& objects, Object& player);

    void BuildScreen(int width, int height, int fontw, int fonth);

    KeyListener getKeyListener();

    void GotoXY(Point _point);
    void MoveTargetObject(Point target_obj);
};