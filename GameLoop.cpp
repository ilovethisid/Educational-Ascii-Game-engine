#include "GameLoop.hpp"

GameLoop::GameLoop()
{
    mv_fps = 24;
    mv_console = Console();
    mv_key_listener = KeyListener();
}

/* Build console window. */
void GameLoop::BuildScreen(int width, int height, int fontw, int fonth)
{

    mv_console.make_console(width, height, fontw, fonth);
    vHideConsoleCursor();
}

/* Returns user built console object */
Console GameLoop::getConsole()
{
    return mv_console;
}

/* Set frame per second. Default FPS is 24. */
void GameLoop::setFPS(double frames)
{
    mv_fps = frames;
}

/* Returns millisec unit time interval per frame. */
DWORD GameLoop::vGetUnitTime()
{
    double unit_time = 1.0 / mv_fps;
    return unit_time * 1000;
}

/* Moves target object */
void GameLoop::UpdateScreen()
{
    Point targetPoint = Point(4, 6);
    int inputKey;

    clock_t start, end, interval, remaining_time;

    Point unitX = Point(1, 0);
    Point unitY = Point(0, 1);             // <------- Prototype of target object. Will be removed later.


    MATRIX* pnt_circle = mv_console.make_circle(10);
    MATRIX* pnt_square = mv_console.make_square(6, 10);

    int x1 = 100;
    int y1 = 100;

    while (true) {
        
        start = clock();                 // start timer

        vGotoXY(targetPoint);

        mv_console.set_tmpbufScreen();
        mv_console.tmp_draw_matrix(targetPoint.getX(), targetPoint.getY(), *pnt_circle);
        mv_console.tmp_draw_matrix(x1--, y1--, *pnt_square);
        mv_console.update();               // <------- Prototype of target object. Will be removed later.


 // Implementation of KeyListener
 /*
        if (mv_key_listener.keycheck(VK_UP)){
            // do something
            targetPoint = targetPoint - unitY;
        }
        else if (mv_key_listener.keycheck(VK_DOWN)){
            // do something
            targetPoint = targetPoint + unitY;
        }
        else if (mv_key_listener.keycheck(VK_LEFT)){
            // do something
            targetPoint = targetPoint - unitX;
        }
        else if (mv_key_listener.keycheck(VK_RIGHT)){
            // do something
            targetPoint = targetPoint + unitX;
        }

        // check if target object goes outside of console window.
        if (targetPoint.getX() < 0)
            targetPoint = targetPoint + unitX;
        else if (targetPoint.getY() < 0)
            targetPoint = targetPoint + unitY;

        // clear old circle
        mv_console.draw_circle(oldPoint.getX(), oldPoint.getY(), 4, ' ');  // <------- Prototype of target object. Will be removed later.
*/

        // Old implementation of key listener
        if (_kbhit()) {
            inputKey = _getch();

            Point oldPoint = targetPoint;

            if (inputKey == 224) {
                inputKey = _getch();

                switch (inputKey) {
                case KEY_UP:
                    targetPoint = targetPoint - unitY; break;
                case KEY_DOWN:
                    targetPoint = targetPoint + unitY; break;
                case KEY_LEFT:
                    targetPoint = targetPoint - unitX; break;
                case KEY_RIGHT:
                    targetPoint = targetPoint + unitX; break;
                }
            }


            // check if target object goes outside of console window.
            if (targetPoint.getX() < 0)
                targetPoint = targetPoint + unitX;
            else if (targetPoint.getY() < 0)
                targetPoint = targetPoint + unitY;
        }


        end = clock();                // end timer

        interval = end - start;    // total elapsed time during a iteration


        vGotoXY(Point(0, 90));      // move cursor to bottom of window

        std::cout << "current FPS is " << mv_fps << std::endl;
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