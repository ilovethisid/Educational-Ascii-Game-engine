/*
    Eduactional Game Engine for Windows Based system.
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

class GameLoop {

private:
    double fps_;
    Console console_;
    bool is_pause_;
    bool is_gameover_;
    int key_pause_;
    int key_resume_;
   
    KeyListener key_listener_;
  //  std::thread* temp_;
    clock_t start_, end_, remaining_time_;
    void vHideConsoleCursor();
    DWORD vGetUnitTime();
    void vCheckPause();
    void vCheckResume();
    void vPrintInfo();

public:
    vector<Object*> objects;
    gameloop_t keythread;
    GameLoop();
    Console getConsole();

    void initialize();
    void setFPS(double frames);

    void start();
    void update();
    void exitLoop();

    void setPauseKey(int key);
    void setResumeKey(int key);
    void checkMove(Object& obj);

    vector<Matrix> MV;//enemy 그림 벡터
    void makeEnemy(); //시간에 따라 enemy 발생

    void checkKey(vector<Object*>& objects);
    void checkShoot(vector<Object*>& objects, Object& player);

    void BuildScreen(int width, int height, int fontw, int fonth);

    KeyListener getKeyListener();

    void GotoXY(Point _point);
    void MoveTargetObject(Point target_obj);
};