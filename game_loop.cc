#include "game_loop.h"

extern void KeyListenerThread();
extern KeyListener klc;

GameLoop::GameLoop()
{
    fps_ = 30;
    console_ = Console();
    key_listener_ = KeyListener();
    temp_ = new std::thread(KeyListenerThread);//이 주소를 gameloop클래스에 저장해주세요
}

/* Build console window. */
void GameLoop::BuildScreen(int _width, int _height, int _fontw, int _fonth)
{
    console_.makeConsole(_width, _height, _fontw, _fonth);
    vHideConsoleCursor();
}

/* Returns user built console object */
Console GameLoop::getConsole()
{
    return console_;
}

/* Set frame per second. Default FPS is 30. */
void GameLoop::setFPS(double _frames)
{
    fps_ = _frames;
}

/* Returns millisec unit time interval per frame. */
DWORD GameLoop::vGetUnitTime()
{
    double unit_time = 1.0 / fps_;
    return unit_time * 1000;
}

KeyListener GameLoop::getKeyListener()
{
    return klc;
}

void GameLoop::StartFrameUpdate()
{
    start_ = clock();               // start timer
}

/* Update console screen */
void GameLoop::FinishFrameUpdate(boolean is_print_info)
{
    clock_t interval;

    console_.update();
    end_ = clock();                 // end timer
    interval = end_ - start_;       // total elapsed time during a iteration
    remaining_time_ = vGetUnitTime() - interval;             // remaining time to sleep

    if (is_print_info) vPrintInfo();

    Sleep(remaining_time_);
}

void GameLoop::vPrintInfo()
{
    clock_t interval;

    GotoXY(Point(0, 90));      // move cursor to bottom of window

    std::cout << "current FPS is " << fps_ << std::endl;
    std::cout << "vGetUnitTime() is " << vGetUnitTime() << "ms" << std::endl;

    interval = end_ - start_;       // total elapsed time during a iteration
    std::cout << "interval is " << interval << "ms" << std::endl;

    std::cout << "remaining_time is " << remaining_time_ << "ms" << std::endl;
}

/* Moves console cursor position */
void GameLoop::GotoXY(Point _point)
{
    COORD pos = {(short) _point.getX(), (short) _point.getY()};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/* Set standard console cursor not visible */
void GameLoop::vHideConsoleCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
