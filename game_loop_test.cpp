#include "game_loop.h"

Object circle1, square1;

const Point kUnitX = Point(1, 0);
const Point kUnitY = Point(0, 1);

Point target_point;

void makeFigures(GameLoop* game_loop);
void checkMove(GameLoop* game_loop);
void checkShot(GameLoop* game_loop);

int main(void)
{
    GameLoop* game_loop = new GameLoop();
    game_loop->setFPS(12);
    game_loop->BuildScreen(160, 100, 8, 8);

    // 최초 그림 그려지는 점 초기화
    target_point = Point(4, 6);

    makeFigures(game_loop);

    Sound my_sound = Sound();
    my_sound.playSound("hello.wav");


    while (true) {

        game_loop->StartFrameUpdate();



        game_loop->getConsole().setTmpBufScreen();
        game_loop->getConsole().drawTmpObject(circle1);
        game_loop->getConsole().drawTmpObject(square1);

        circle1.move(game_loop->objects);
        square1.move(game_loop->objects);


        checkMove(game_loop);
        checkShot(game_loop);

        game_loop->FinishFrameUpdate(true);
        
        game_loop->GotoXY(target_point);
        std::cout << target_point.getX() << ", " << target_point.getY() << std::endl;
    }


    return 0;
}


void makeFigures(GameLoop* game_loop)
{
    // 그릴 도형의 행렬 초기화
    Matrix mat_circle = game_loop->getConsole().makeCircle(10);
    Matrix mat_square = game_loop->getConsole().makeSquare(6, 10);

    //도형 초기화
    circle1 = Object(target_point.getX(), target_point.getY());
    circle1.makeImage(mat_circle);
    circle1.makeRigidbody();
    circle1.rigidbody.setVelocity(1, 1);
    circle1.rigidbody.makeMatrixCollider(mat_circle);

    square1 = Object(100, 100);
    square1.makeImage(mat_square);
    square1.makeRigidbody();
    square1.rigidbody.setVelocity(-1, -1);
    square1.rigidbody.makeMatrixCollider(mat_square);

    // 도형들을 vector에 append
    game_loop->objects.push_back(&circle1);
    game_loop->objects.push_back(&square1);
}


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


void checkShot(GameLoop* game_loop)
{
    Point shot_point;

    if (game_loop->getKeyListener().keycheck(eag_space)) {
        shot_point = target_point;
        std::cout << "space!!!" << std::endl;
    }

    shot_point = shot_point - kUnitY;
    game_loop->GotoXY(shot_point);
    std::cout << ", " << std::endl;

    game_loop->GotoXY(target_point);
}