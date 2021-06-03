#include "game_loop.h"

extern void KeyListenerThread();
extern KeyListener klc;


///////////////////////// 비행기 게임 부위
//class Player_Plane
//{
//private:
//    Object plane;
//    int life;
//    int power;
//public:
//    void moveByKey() {
//        if (klc.keycheck(eag_Top)) {
//            plane.rigidbody.setVelocity(0, -2);
//            if (klc.keycheck(eag_Left))
//                plane.rigidbody.setVelocity(-2, -2);
//            else if (klc.keycheck(eag_Right))
//                plane.rigidbody.setVelocity(2, -2);
//        }
//        else if (klc.keycheck(eag_Bottom)) {
//            plane.rigidbody.setVelocity(0, 2);
//            if (klc.keycheck(eag_Left))
//                plane.rigidbody.setVelocity(-2, 2);
//            else if (klc.keycheck(eag_Right))
//                plane.rigidbody.setVelocity(2, 2);
//        }
//        else if (klc.keycheck(eag_Left)) {
//            plane.rigidbody.setVelocity(-2, 0);
//        }
//        else if (klc.keycheck(eag_Right)) {
//            plane.rigidbody.setVelocity(2, 0);
//        }
//        else {
//            plane.rigidbody.setVelocity(0, 0);
//        }
//    }
//};
//




/////////////////////////



GameLoop::GameLoop()
{
    fps_ = 30;
    is_pause_ = false;
    is_gameover_ = false;
    console_ = Console();
    gameloop_t keythread;
    keythread.start();
}

/* Build console window. */
void GameLoop::BuildScreen(int _width, int _height, int _fontw, int _fonth)
{
    console_.makeConsole(_width, _height, _fontw, _fonth);
    vHideConsoleCursor();
}

KeyListener GameLoop::getKeyListener()
{
    return klc;
}

/* Returns user built console object */
Console GameLoop::getConsole()
{
    return console_; 
}

// 임시 함수, 나중에 제거 예정
void GameLoop::initialize()
{
    int x = 0;
    int y = 0;
    int x1 = 100;
    int y1 = 100;
    Object* obj1 = new Object(20, 60);
    Object* obj2 = new Object(30, 40);

    //Matrix background = console_.makeFile2Matrix("C:\\Users\\정훈석\\Desktop\\깃헙 소공\\Educational-Ascii-Game-engine\\background");//파일 경로
    Matrix background = console_.makeFile2Matrix("C:\\Users\\andre\\Desktop\\fps\\Educational-Ascii-Game-engine\\background");

    console_.drawMatrix(0, 0, background);

    //Matrix matrix1 = console_.makeFile2Matrix("C:\\Users\\정훈석\\Desktop\\깃헙 소공\\Educational-Ascii-Game-engine\\plane");
    Matrix matrix1 = console_.makeFile2Matrix("C:\\Users\\andre\\Desktop\\fps\\Educational-Ascii-Game-engine\\plane");
    Matrix matrix2 = console_.makeCircle(5);


    obj1->makeRigidbody();
    obj2->makeRigidbody();

    obj1->makeImage(matrix1);
    obj2->makeImage(matrix2);

    obj1->rigidbody.makeMatrixCollider(matrix1);
    obj2->rigidbody.makeMatrixCollider(matrix2);



    objects.push_back(obj1);
    objects.push_back(obj2);
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

    while (!is_gameover_) {
        if (!is_pause_) {
            start = clock();                 // start timer
            update();
            end = clock();                // end timer

            interval = end - start;    // total elapsed time during a iteration
            remaining_time = vGetUnitTime() - interval;             // remaining time to sleep

            Sleep(remaining_time);
        }
        checkResume();
    }
}

void GameLoop::update()
{
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->move(objects);
    }
    console_.setTmpBufScreen();

    checkMove(*objects[0]);

    console_.drawTmpObjects(objects);
    console_.update();

}

void GameLoop::pause()
{
    if (!is_pause_) is_pause_ = true;
}

void GameLoop::resume()
{
    if (is_pause_) is_pause_ = false;
}

void GameLoop::exitLoop()
{
    is_gameover_ = true;
}

// Implementation of KeyListener
void GameLoop::checkMove(Object& obj)
{
    if (klc.keycheck(eag_Top)) {
        obj.rigidbody.setVelocity(0, -2);
        if (klc.keycheck(eag_Left))
            obj.rigidbody.setVelocity(-2, -2);
        else if (klc.keycheck(eag_Right))
            obj.rigidbody.setVelocity(2, -2);
    }
    else if (klc.keycheck(eag_Bottom)) {
        obj.rigidbody.setVelocity(0, 2);
        if (klc.keycheck(eag_Left))
            obj.rigidbody.setVelocity(-2, 2);
        else if (klc.keycheck(eag_Right))
            obj.rigidbody.setVelocity(2, 2);
    }
    else if (klc.keycheck(eag_Left)) {
        obj.rigidbody.setVelocity(-2, 0);
    }
    else if (klc.keycheck(eag_Right)) {
        obj.rigidbody.setVelocity(2, 0);
    }
    else if (klc.keycheck(eag_space)) {
        pause();
    }
    else {
        obj.rigidbody.setVelocity(0, 0);
    }
}

void GameLoop::checkResume()
{
    if (is_pause_) {
        if (klc.keycheck(eag_space)) {
            resume();
        }
    }

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
