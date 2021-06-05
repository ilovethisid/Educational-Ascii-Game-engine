#include "game_loop.h"

extern KeyListener g_klc;

GameLoop::GameLoop()
{
    fps_ = 30;
    is_pause_ = false;
    is_gameover_ = false;
    key_pause_ = EOF;
    key_resume_ = EOF;
    console_ = Console();
    keythread.start();
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
    return g_klc;
}

/* Returns user built console object */
Console& GameLoop::getConsole()
{
    return console_; 
}

// 임시 함수, 나중에 제거 예정
void GameLoop::initialize()
{
    //경로 알아서 지정
    Matrix M1 = console_.makeFile2Matrix("./usrlib/enemy1");
    Matrix M2 = console_.makeFile2Matrix("./usrlib/enemy2");
    Matrix M3 = console_.makeFile2Matrix("./usrlib/enemy3");
    MV.push_back(M1);
    MV.push_back(M2);
    MV.push_back(M3);
}

/* Set frame per second. Default FPS is 30. */
void GameLoop::setFPS(double _frames)
{
    fps_ = _frames;
}

void GameLoop::start()
{
    clock_t start, end, interval, remaining_time;
    bool gameover = 0;
    initialize();

    int last_time = clock();

    while (!is_gameover_) {
        vCheckPause();
        start = clock();                 // start timer

        if ((start - last_time) > 1000) {//when passed make enemy
            makeEnemy();
            last_time = start;
        }

        vUpdate();
        end = clock();                // end timer

        interval = end - start;    // total elapsed time during a iteration
        remaining_time = vGetUnitTime() - interval;             // remaining time to sleep

        Sleep(remaining_time);
    }
}


void GameLoop::vUpdate()
{
    checkKey();
    updateLoop();

    console_.setTmpBufScreen();
    console_.drawTmpObjects(objects);
    console_.update();
}

void GameLoop::checkKey() {}
void GameLoop::updateLoop() {}


/* If key_pause_ is pressed, pause game loop. */
void GameLoop::vCheckPause()
{
    if (GetAsyncKeyState(g_klc.eagKeyToVK(key_pause_)))
        vCheckResume();
}

void GameLoop::vCheckResume()
{
    Sleep(100);
    while (true) {
        if (GetAsyncKeyState(g_klc.eagKeyToVK(key_resume_)) & 0x8000) {
            g_klc.reset();
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

void GameLoop::makeEnemy() { //적발생

    int rand_num = rand();
    Object* enemy = new Object(140 / (rand_num % 4 + 1), 2);
    enemy->makeImage(MV[rand_num % 3]); //모양 3개
    enemy->makeRigidbody();
    enemy->rigidbody.makeMatrixCollider(MV[rand_num % 3]);
    enemy->setName("enemy");
    enemy->rigidbody.setVelocity((rand_num % 4 - 2), rand_num % 3 + 1);
    objects.push_back(enemy);
}

