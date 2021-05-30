#include "game_loop.h"

extern void KeyListenerThread();
extern KeyListener klc;


///////////////////////// 비행기 게임 부위
class Player_Plane
{
private:
    Object plane;
    int life;
    int power;
public:
    void moveByKey() {
        if (klc.keycheck(eag_Top)) {
            plane.rigidbody.setVelocity(0, -2);
            if (klc.keycheck(eag_Left))
                plane.rigidbody.setVelocity(-2, -2);
            else if (klc.keycheck(eag_Right))
                plane.rigidbody.setVelocity(2, -2);
        }
        else if (klc.keycheck(eag_Bottom)) {
            plane.rigidbody.setVelocity(0, 2);
            if (klc.keycheck(eag_Left))
                plane.rigidbody.setVelocity(-2, 2);
            else if (klc.keycheck(eag_Right))
                plane.rigidbody.setVelocity(2, 2);
        }
        else if (klc.keycheck(eag_Left)) {
            plane.rigidbody.setVelocity(-2, 0);
        }
        else if (klc.keycheck(eag_Right)) {
            plane.rigidbody.setVelocity(2, 0);
        }
        else {
            plane.rigidbody.setVelocity(0, 0);
        }
    }
};





/////////////////////////



GameLoop::GameLoop()
{
    fps_ = 30;
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

void GameLoop::initialize( vector<Object*>& objects)
{
    int x = 0;
    int y = 0;
    int x1 = 100;
    int y1 = 100;
    Object* obj1 = new Object(20, 20);
    Object* obj2 = new Object(70, 70);


    Matrix matrix1 = console_.makeCircle(10, 0x263A, BG_DARK_BLUE);
    Matrix matrix2 = console_.makeTriangle(0, 20, 5, 2, 10, 24, PIXEL_SOLID, FG_BLUE);

    console_.draw(1, 1, 0x263A, 0b00001010);
    console_.draw(1, 2, 9608, 0b00000010);
    console_.draw(1, 3, 9608, 0b00001010);
    console_.draw(1, 4, 9608, 4);
    console_.draw(1, 5, 9608, 5);
    console_.draw(1, 6, 9608, 6);
    console_.draw(1, 7, 9608, 7);
    console_.draw(1, 8, 9608, 8);
    console_.draw(1, 9, 9608, 9);
    console_.draw(1, 10, 9608, 10);
    console_.draw(1, 11, 9608, 11);
    console_.draw(1, 12, 9608, 12);
    console_.draw(1, 13, 9608, 13);
    console_.draw(1, 14, 9608, 14);
    console_.draw(1, 15, 9608, 15);

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

void GameLoop::start( vector<Object*>& objects)
{
    clock_t start, end, interval, remaining_time;
    bool gameover = 0;

    initialize( objects);

    while (!gameover) {

        start = clock();                 // start timer

        end = clock();                // end timer

        interval = end - start;    // total elapsed time during a iteration

        update(objects);

        remaining_time = vGetUnitTime() - interval;             // remaining time to sleep

        Sleep(remaining_time);
    }
}

void GameLoop::update( vector<Object*>& objects)
{
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->move(objects);
    }
    console_.setTmpBufScreen();

    checkMove(*objects[0]);

    console_.drawTmpObjects(objects);
    console_.update();
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
