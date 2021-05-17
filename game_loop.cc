#include "game_loop.h"

GameLoop::GameLoop()
{
    fps_ = 24;
    console_ = Console();
    key_listener_ = KeyListener();
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

/* Set frame per second. Default FPS is 24. */
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


    MATRIX* pnt_circle = console_.make_circle(10);
    MATRIX* pnt_square = console_.make_square(6, 10);

    int x1 = 100;
    int y1 = 100;

    while (true) {
        
        start = clock();                 // start timer

        vGotoXY(target_point);

        console_.set_tmpbufScreen();
        console_.tmp_draw_matrix(target_point.getX(), target_point.getY(), *pnt_circle);
        console_.tmp_draw_matrix(x1--, y1--, *pnt_square);
        console_.update();               // <------- Prototype of target object. Will be removed later.


 // Implementation of KeyListener
 /*
        if (key_listener_.keycheck(VK_UP)) {
            // do something
            target_point = target_point - kUnitY;
        }
        else if (key_listener_.keycheck(VK_DOWN)) {
            // do something
            target_point = target_point + kUnitY;
        }
        else if (key_listener_.keycheck(VK_LEFT)) {
            // do something
            target_point = target_point - kUnitX;
        }
        else if (key_listener_.keycheck(VK_RIGHT)) {
            // do something
            target_point = target_point + kUnitX;
        }

        // check if target object goes outside of console window.
        if (target_point.getX() < 0)
            target_point = target_point + kUnitX;
        else if (target_point.getY() < 0)
            target_point = target_point + kUnitY;

        // clear old circle
        console_.draw_circle(oldPoint.getX(), oldPoint.getY(), 4, ' ');  // <------- Prototype of target object. Will be removed later.
*/

        // Old implementation of key listener
        if (_kbhit()) {
            inputKey = _getch();

            Point oldPoint = target_point;

            if (inputKey == 224) {
                inputKey = _getch();

                switch (inputKey) {
                case KEY_UP:
                    target_point = target_point - kUnitY; break;
                case KEY_DOWN:
                    target_point = target_point + kUnitY; break;
                case KEY_LEFT:
                    target_point = target_point - kUnitX; break;
                case KEY_RIGHT:
                    target_point = target_point + kUnitX; break;
                }
            }


            // check if target object goes outside of console window.
            if (target_point.getX() < 0)
                target_point = target_point + kUnitX;
            else if (target_point.getY() < 0)
                target_point = target_point + kUnitY;
        }


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