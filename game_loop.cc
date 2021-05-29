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

KeyListener GameLoop::getKeyListener()
{
    return klc;
}

/* Returns user built console object */
Console GameLoop::getConsole()
{
    return console_;
}

void GameLoop::initialize(Console demo, vector<Object*>& objects)
{
    int x = 0;
    int y = 0;
    int x1 = 100;
    int y1 = 100;
    Object* obj1 = new Object(20, 20);
    Object* obj2 = new Object(70, 70);
    Object* obj3 = new Object(1, 1);

    Matrix matrix1 = demo.makeCircle(10);
    Matrix matrix2 = demo.makeTriangle(0, 20, 5, 2, 10, 24);
    Matrix matrix3 = demo.makeSquare(4, 10);

    obj1->makeRigidbody();
    obj2->makeRigidbody();
    obj3->makeRigidbody();
    obj1->makeImage(matrix1);
    obj2->makeImage(matrix2);
    obj3->makeImage(matrix3);
    obj1->rigidbody.setVelocity(1, 1);
    obj3->rigidbody.setVelocity(1, 1);
    obj1->rigidbody.makeMatrixCollider(matrix1);
    obj2->rigidbody.makeMatrixCollider(matrix2);
    obj3->rigidbody.makeMatrixCollider(matrix3);


    objects.push_back(obj1);
    objects.push_back(obj2);
}

/* Set frame per second. Default FPS is 30. */
void GameLoop::setFPS(double _frames)
{
    fps_ = _frames;
}

void GameLoop::start(Console demo, vector<Object*>& objects)
{
    clock_t start, end, interval, remaining_time;
    bool gameover = 0;

    initialize(demo, objects);

    while (!gameover) {

        start = clock();                 // start timer

        end = clock();                // end timer

        interval = end - start;    // total elapsed time during a iteration

        update(demo, objects);

        remaining_time = vGetUnitTime() - interval;             // remaining time to sleep

        Sleep(remaining_time);
    }
}

void GameLoop::update(Console demo, vector<Object*>& objects)
{
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->move(objects);
    }

    checkMove(*objects[0]);

    demo.setTmpBufScreen();
    demo.drawTmpObjects(objects);
    demo.update();
}

// Implementation of KeyListener
void GameLoop::checkMove(Object& obj)
{
    if (getKeyListener().keycheck(eag_Top)) {
        obj.rigidbody.setVelocity(0, -1);
    }
    else if (getKeyListener().keycheck(eag_Bottom)) {
        obj.rigidbody.setVelocity(0, 1);
    }
    else if (getKeyListener().keycheck(eag_Left)) {
        obj.rigidbody.setVelocity(-1, 0);
    }
    else if (getKeyListener().keycheck(eag_Right)) {
        obj.rigidbody.setVelocity(1, 0);
    }
    else {
        obj.rigidbody.setVelocity(0, 0);
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
