#include "game_loop.h"

extern KeyListener klc;

GameLoop::GameLoop()
{
    fps_ = 30;
    is_pause_ = false;
    is_gameover_ = false;
    key_pause_ = EOF;
    key_resume_ = EOF;
    console_ = Console();
    key_thread_.start();
    vSetCwdToEnginePath();
}

/* Build console window. */
void GameLoop::buildScreen(int _width, int _height, int _fontw, int _fonth)
{
    console_.makeConsole(_width, _height, _fontw, _fonth);
    vHideConsoleCursor();
}

KeyListener& GameLoop::getKeyListener()
{
    return klc;
}

/* Returns user built console object */
Console& GameLoop::getConsole()
{
    return console_; 
}

/* Set frame per second. Default FPS is 30. */
void GameLoop::setFPS(double _frames)
{
    fps_ = _frames;
}

void GameLoop::start()
{
    initialize();

    while (!is_gameover_) {
        vCheckPause();
        vUpdate();
    }
}

void GameLoop::initialize() {}

/* If key_pause_ is pressed, pause game loop. */
void GameLoop::vCheckPause()
{
    if (klc.keycheck(key_pause_)) {
        klc.reset();
        vCheckResume();
    }
}

void GameLoop::vUpdate()
{
    clock_t start, end, interval, remaining_time;

    start = clock();                 // start timer
    checkKey();

    console_.setTmpBufScreen();
    updateLoop(); //updateLoop À§Ä¡¹Ù²Þ;
    console_.drawTmpObjects(objects);
    console_.update();
    end = clock();                // end timer

    interval = end - start;    // total elapsed time during a iteration
    remaining_time = vGetUnitTime() - interval;             // remaining time to sleep

    Sleep(remaining_time);
}

void GameLoop::checkKey() {}
void GameLoop::updateLoop() {}

void GameLoop::vCheckResume()
{
    Sleep(RESET_DELAY);
    while (true) {
        if (klc.keycheck(key_resume_)) {
            klc.reset();
            return;
        }
    }
}

void GameLoop::setPauseKey(int key)
{
    key_pause_ = key;
}

void GameLoop::setResumeKey(int key)
{
    key_resume_ = key;
}

void GameLoop::exit()
{
    is_gameover_ = true;
}

/* Returns millisec unit time interval per frame. */
DWORD GameLoop::vGetUnitTime()
{
    double unit_time = 1.0 / fps_;
    return unit_time * 1000;
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

/* Get EAG engine absolute path */
char* GameLoop::getEnginePath()
{
    char origin[] = __FILE__;
    char dest[100];

    const char* source_file = strrchr(origin, '\\');
    strncpy_s(dest, origin, source_file - origin);
    return dest;
}

/* Change current working directory to EAG engine path */
void GameLoop::vSetCwdToEnginePath()
{
    int nResult = _chdir(getEnginePath());
    if (nResult) {
        std::cout << "Invalid EAG engine path" << std::endl;
        std::exit(1);
    }
}
