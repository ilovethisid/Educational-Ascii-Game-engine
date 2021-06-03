
#include "game_loop.h"

Object circle1, square1;

const Point kUnitX = Point(1, 0);
const Point kUnitY = Point(0, 1);

Point target_point;

void makeFigures(GameLoop* game_loop);
/*
void checkMove(GameLoop* game_loop);
*/

void checkShot(GameLoop* game_loop);

int main(void)
{
    GameLoop* game_loop = new GameLoop();
    game_loop->setFPS(12);
    game_loop->BuildScreen(160, 100, 8, 8);

    // ���� �׸� �׷����� �� �ʱ�ȭ
    target_point = Point(20, 20);

    makeFigures(game_loop);

    Sound my_sound = Sound();
    my_sound.playSound("hello.wav");

    vector<Object*> objects;
    game_loop->start(objects);

    /*while (true) {

        game_loop->start();



        game_loop->getConsole().setTmpBufScreen();
        game_loop->getConsole().drawTmpObject(circle1);
        game_loop->getConsole().drawTmpObject(square1);

        circle1.move(game_loop->objects);
        square1.move(game_loop->objects);


        checkMove(game_loop);
        checkShot(game_loop);

        game_loop->FinishFrameUpdate(true);
        
        game_loop->GotoXY(target_point);
    }*/

    return 0;
}


void makeFigures(GameLoop* game_loop)
{
    // �׸� ������ ��� �ʱ�ȭ
    Matrix mat_circle = game_loop->getConsole().makeCircle(10);
    Matrix mat_box = game_loop->getConsole().makeBox(game_loop->getConsole().getScreenWidth(), game_loop->getConsole().getScreenHeight());

    //���� �ʱ�ȭ
    circle1 = Object(target_point.getX(), target_point.getY());
    circle1.makeImage(mat_circle);
    circle1.makeRigidbody();
    circle1.rigidbody.setVelocity(0, 0);
    circle1.rigidbody.makeMatrixCollider(mat_circle);

    Object* boundary = new Object(0, 0);
    boundary->makeImage(mat_box);
    boundary->makeRigidbody();
    boundary->rigidbody.makeMatrixCollider(mat_box);
    boundary->setName("boundary");

    // �������� vector�� append
    game_loop->objects.push_back(boundary);
    game_loop->objects.push_back(&circle1);
}

/*
// Implementation of KeyListener
void checkMove(GameLoop* game_loop)
{
    if (game_loop->getKeyListener().keycheck(eag_Top)) {
        circle1.rigidbody.setVelocity(0, -1);
    }
    else if (game_loop->getKeyListener().keycheck(eag_Bottom)) {
        circle1.rigidbody.setVelocity(0, 1);
    }
    else if (game_loop->getKeyListener().keycheck(eag_Left)) {
        circle1.rigidbody.setVelocity(-1, 0);
    }
    else if (game_loop->getKeyListener().keycheck(eag_Right)) {
        circle1.rigidbody.setVelocity(1, 0);
    }
}
*/

void checkShot(GameLoop* game_loop)
{
    Point shot_point;

    if (game_loop->getKeyListener().keycheck(eag_space)) {
        shot_point = target_point;
    }

    shot_point = shot_point - kUnitY;
    game_loop->GotoXY(shot_point);
    game_loop->GotoXY(target_point);
}
