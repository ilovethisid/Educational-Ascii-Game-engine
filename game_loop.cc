#include <iostream>
#include "game_loop.h"

extern void KeyListenerThread();
extern KeyListener klc;


///////////////////////// ����� ���� ����
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

// �ӽ� �Լ�, ���߿� ���� ����
void GameLoop::initialize()
{
    int x = 0;
    int y = 0;
    int x1 = 100;
    int y1 = 100;
    Object* obj1 = new Object(20, 60);
    Object* obj2 = new Object(30, 40);

    Matrix background = console_.makeFile2Matrix("C:\\Users\\���Ƽ�\\Desktop\\���� �Ұ�\\Educational-Ascii-Game-engine\\background");//���� ���
    //Matrix background = console_.makeFile2Matrix("C:\\Users\\andre\\Desktop\\fps\\Educational-Ascii-Game-engine\\background");
    
    // ����
    //Matrix background = console_.makeFile2Matrix("C:\\Users\\ilove\\source\\repos\\Educational-Ascii-Game-engine\\background");//���� ���


    console_.drawMatrix(0, 0, background);

    Matrix matrix1 = console_.makeFile2Matrix("C:\\Users\\���Ƽ�\\Desktop\\���� �Ұ�\\Educational-Ascii-Game-engine\\plane");
    //Matrix matrix1 = console_.makeFile2Matrix("C:\\Users\\andre\\Desktop\\fps\\Educational-Ascii-Game-engine\\plane");

    // ���� 
    //Matrix matrix1 = console_.makeFile2Matrix("C:\\Users\\ilove\\source\\repos\\Educational-Ascii-Game-engine\\plane");
    

    Matrix matrix2 = console_.makeCircle(5);
    
    console_.drawMatrix(0, 0, background);

    

    obj1->makeRigidbody();

    obj1->makeImage(matrix1);

    obj1->setName("player");

    obj1->rigidbody.makeMatrixCollider(matrix1);

    objects.push_back(obj1);
}

/* Set frame per second. Default FPS is 30. */
void GameLoop::setFPS(double _frames)
{
    fps_ = _frames;
}

void GameLoop::start(vector<Object*>& objects)
{
    clock_t start, end, interval, remaining_time;
    bool gameover = 0;
    objects = objects;
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
    //Object* player = objects[0]->findByName(objects, "player");

    checkKey(objects);

    for (int i = 0; i < objects.size(); i++) {
        objects[i]->move(objects);
    }
    // move according to velocity

    console_.setTmpBufScreen();

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

void GameLoop::checkKey(vector<Object*>& objects)
{
    Object* player = objects[0]->findByName(objects, "player");

    checkMove(*player);
    checkShoot(objects, *player);
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

    /*else if (klc.keycheck(eag_space)) {
        pause();
    }*/
    // space �Ѿ� ��°ɷ� �ؼ�...

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

void GameLoop::checkShoot(vector<Object*>& objects, Object& player)
{
    if (klc.keycheck(eag_space)) {
        Object* bullet;
        bullet = new Object(player.getX() + player.getImage().width / 2, player.getY() - 2);
        Matrix image = Matrix(1, 1);
        image.element[0][0] = '|';
        bullet->makeImage(image);
        bullet->makeRigidbody();
        bullet->rigidbody.makeMatrixCollider(image);
        bullet->setName("bullet");
        bullet->rigidbody.setVelocity(0, -3);
        objects.push_back(bullet);
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
