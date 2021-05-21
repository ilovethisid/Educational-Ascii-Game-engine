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
    console_.make_console(_width, _height, _fontw, _fonth);
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

/* Moves target object */
void GameLoop::UpdateScreen()
{
    Point target_point = Point(4, 6);
    int inputKey;

    clock_t start, end, interval, remaining_time;

    const Point kUnitX = Point(1, 0);
    const Point kUnitY = Point(0, 1);             // <------- Prototype of target object. Will be removed later.


    Matrix mat_circle = console_.make_circle(10);
    Matrix mat_square = console_.make_square(6, 10);

    Object circle1 = Object(target_point.getX(), target_point.getY());
    circle1.makeImage(mat_circle);
    circle1.makeRigidbody();
    circle1.rigidbody.setVelocity(1, 1);
    circle1.rigidbody.makeMatrixCollider(mat_circle);

    Object square1 = Object(100, 100);
    square1.makeImage(mat_square);
    square1.makeRigidbody();
    square1.rigidbody.setVelocity(-1, -1);
    square1.rigidbody.makeMatrixCollider(mat_square);


    vector<Object*> objects;

    objects.push_back(&circle1);
    objects.push_back(&square1);


    Point shot_point;

    while (true) {
        
        start = clock();                 // start timer

        vGotoXY(target_point);

        console_.set_tmpbufScreen();
        console_.tmp_draw_Object(circle1);
        console_.tmp_draw_Object(square1);

        circle1.move(objects);
        square1.move(objects);
        console_.update();               // <------- Prototype of target object. Will be removed later.


 // Implementation of KeyListener
        if (klc.keycheck(eag_Top)) {
            // do something
            target_point = target_point - kUnitY;
        }
        else if (klc.keycheck(eag_Bottom)) {
            // do something
            target_point = target_point + kUnitY;
        }
        else if (klc.keycheck(eag_Left)) {
            // do something
            target_point = target_point - kUnitX;
        }
        else if (klc.keycheck(eag_Right)) {
            // do something
            target_point = target_point + kUnitX;
        }

        // check if target object goes outside of console window.
        if (target_point.getX() < 0)
            target_point = target_point + kUnitX;
        else if (target_point.getY() < 0)
            target_point = target_point + kUnitY;


        std::cout << target_point.getX() << ", " << target_point.getY() << std::endl;


        if (klc.keycheck(eag_space)) {
            // do something
            shot_point = target_point;
            std::cout << "space!!!" << std::endl;
        }

        shot_point = shot_point - kUnitY;
        vGotoXY(shot_point);
        std::cout << ", " << std::endl;
        vGotoXY(target_point);

        end = clock();                // end timer

        interval = end - start;    // total elapsed time during a iteration


        vGotoXY(Point(0, 90));      // move cursor to bottom of window

        std::cout << "current FPS is " << fps_ << std::endl;
        std::cout << "vGetUnitTime() is " << vGetUnitTime() << "ms" << std::endl;

        std::cout << "interval is " << interval << "ms" << std::endl;

        remaining_time = vGetUnitTime() - interval;             // remaining time to sleep
        std::cout << "remaining_time is " << remaining_time << "ms" << std::endl;

        Sleep(remaining_time);
    }
}

/* Moves console cursor position */
void GameLoop::vGotoXY(Point _point)
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


int main(void)
{
    GameLoop *game_loop = new GameLoop();
    game_loop->setFPS(12);
    game_loop->BuildScreen(160, 100, 8, 8);
    game_loop->UpdateScreen();

    return 0;
}