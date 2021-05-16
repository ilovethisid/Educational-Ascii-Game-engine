#include "FPS.hpp"

FramePerSecond::FramePerSecond()
{
    mvFPS = 24;
    mvConsole = Console();
}

/* Build console window. */
void FramePerSecond::BuildScreen(int width, int height, int fontw, int fonth)
{

    mvConsole.make_console(width, height, fontw, fonth);
    vHideConsoleCursor();
}

/* Returns user built console object */
Console FramePerSecond::getConsole()
{
    return mvConsole;
}

/* Set frame per second. Default FPS is 24. */
void FramePerSecond::setFPS(double frames)
{
    mvFPS = frames;
}

/* Returns millisec unit time interval per frame. */
DWORD FramePerSecond::vGetUnitTime()
{
    double unitTime = 1.0 / mvFPS;
    return unitTime * 1000;
}

/* Moves target object */
void FramePerSecond::UpdateScreen()
{
    Point targetPoint = Point(4, 6);
    int inputKey;

    Point unitX = Point(1, 0);
    Point unitY = Point(0, 1);             // <------- Prototype of target object. Will be removed later.

    while (true) {
        Sleep(vGetUnitTime());
        vGotoXY(targetPoint);

        mvConsole.draw_circle(targetPoint.getX(), targetPoint.getY(), 4);
        mvConsole.update();               // <------- Prototype of target object. Will be removed later.

        if (_kbhit()) {
            Point oldPoint = targetPoint;
            inputKey = _getch();

            if (inputKey == 224) {
                inputKey = _getch();

                switch (inputKey) {
                case KEY_UP:
                    targetPoint = targetPoint.operator-(unitY); break;
                case KEY_DOWN:
                    targetPoint = targetPoint.operator+(unitY);; break;
                case KEY_LEFT:
                    targetPoint = targetPoint.operator-(unitX);; break;
                case KEY_RIGHT:
                    targetPoint = targetPoint.operator+(unitX);; break;
                }
            }

            // check if target object goes outside of console window.
            if (targetPoint.getX() < 0)
                targetPoint = targetPoint.operator+(unitX);
            else if (targetPoint.getY() < 0)
                targetPoint = targetPoint.operator+(unitY);

            // clear old circle
            mvConsole.draw_circle(oldPoint.getX(), oldPoint.getY(), 4, ' ');  // <------- Prototype of target object. Will be removed later.
        }
    }
}


/* Moves target object */
void FramePerSecond::MoveTargetObject(Point target_obj)
{
    int input_key;

    Point unit_x = Point(1, 0);
    Point unit_y = Point(0, 1);             // <------- Prototype of target object. Will be removed later.

    while(true){
        vGotoXY(target_obj);

        printf("¡Ú");                       // <------- Prototype of target object. Will be removed later.

        if (_kbhit()){
            input_key = _getch();

            if (input_key == 224){
                input_key = _getch();

                switch(input_key){
                    case KEY_UP:
                        target_obj = target_obj.operator-(unit_y); break;
                    case KEY_DOWN:
                        target_obj = target_obj.operator+(unit_y);; break;
                    case KEY_LEFT:
                        target_obj = target_obj.operator-(unit_x);; break;
                    case KEY_RIGHT:
                        target_obj = target_obj.operator+(unit_x);; break;
                }
            }
            system("cls");
        }

        // check if target object goes outside of console window.
        if (target_obj.getX() < 0)
            target_obj = target_obj.operator+(unit_x);
        else if (target_obj.getY() < 0)
            target_obj = target_obj.operator+(unit_y);
    }
}

/* Moves console cursor position */
void FramePerSecond::vGotoXY(Point _point)
{
    COORD pos = {(short) _point.getX(), (short) _point.getY()};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/* Set standard console cursor not visible */
void FramePerSecond::vHideConsoleCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}


int main(void)
{
    FramePerSecond *fps = new FramePerSecond();
    fps->setFPS(12);
    fps->BuildScreen(80, 30, 10, 10);
    fps->UpdateScreen();

    return 0;
}