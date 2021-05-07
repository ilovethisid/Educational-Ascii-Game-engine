#include "FPS.hpp"

FramePerSecond::FramePerSecond()
{
    hideConsoleCursor();
}

/* Moves target object */
void FramePerSecond::moveTargetObject(Point target_obj)
{
    int input_key;

    Point unit_x = Point(1, 0);
    Point unit_y = Point(0, 1);             // <------- Prototype of target object. Will be removed later.

    while(true){
        gotoxy(target_obj);

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
void FramePerSecond::gotoxy(Point _point)
{
    COORD pos = {(short) _point.getX(), (short) _point.getY()};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/* Set standard console cursor not visible */
void FramePerSecond::hideConsoleCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}


int main(void)
{
    Point my_target_object = Point();

    FramePerSecond fps;
    fps.moveTargetObject(my_target_object);
    
    return 0;
}