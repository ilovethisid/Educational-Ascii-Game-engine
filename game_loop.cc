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
    life = 5;
    score = 0;
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
    if (GetAsyncKeyState(klc.eagKeyToVK(key_pause_)))
        vCheckResume();
}

void GameLoop::vUpdate()
{
    clock_t start, end, interval, remaining_time;

    start = clock();                 // start timer
    checkKey();
    updateLoop();

    console_.setTmpBufScreen();
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
    Sleep(100);
    while (true) {
        if (GetAsyncKeyState(klc.eagKeyToVK(key_resume_)) & 0x8000) {
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
void GameLoop::drawlife()
{
    Matrix life_image;
    life_image.width = 10;
    life_image.height = 1;
    life_image.color = new unsigned char[1 * 10];
    for (int i = 0; i < 10; i++)
    {
        life_image.color[i] = FG_RED;
    }
    life_image.element = new short* [1];
    for (int i = 0; i < 1; i++)
    {
        life_image.element[i] = new short[10];
    }
    for (int i = 0; i < 5; i++)
    {
        life_image.element[0][2 * i] = L'¢¾';
        life_image.element[0][2 * i + 1] = L' ';
    }
    console_.drawMatrix(5, 2, life_image);
}

void GameLoop::minuslife()
{
    Matrix null_image;
    null_image.width = 1;
    null_image.height = 1;
    null_image.color = new unsigned char[1];
    null_image.color[0] = FG_BLACK;
    null_image.element = new short* [1];
    null_image.element[0] = new short[1];
    null_image.element[0][0] = L' ';
    if (life > 0)
    {
        console_.drawMatrix(3 + life * 2, 2, null_image);
        life--;
    }
    else
    {
        exitLoop();
    }
}
void GameLoop::addlife()
{
    Matrix null_image;
    null_image.width = 1;
    null_image.height = 1;
    null_image.color = new unsigned char[1];
    null_image.color[0] = FG_RED;
    null_image.element = new short* [1];
    null_image.element[0] = new short[1];
    null_image.element[0][0] = L'¢¾';
    if (life < 5)
    {
        console_.drawMatrix(5 + life * 2, 2, null_image);
        life++;
    }
}
void GameLoop::addscore(int _score)
{
    this->score = this->score + _score;
    int temp = this->score;
    Matrix score_image;
    score_image.width = 20;
    score_image.height = 1;
    score_image.color = new unsigned char[20];
    for (int i = 0; i < 20; i++)
    {
        score_image.color[i] = FG_WHITE;
    }
    score_image.element = new short* [1];
    score_image.element[0] = new short[20];
    for (int i = 0; i < 20; i++)
    {
        score_image.element[0][19 - i] = L'0' + temp % 10;
        temp = temp / 10;
    }
    console_.drawMatrix(40, 2, score_image);
}
