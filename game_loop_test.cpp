

#include <cstdlib>  // system()�� ���� ��� ����



#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>//�޸� ����

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#include "game_loop.h"

Object circle1, square1;

const Point kUnitX = Point(1, 0);
const Point kUnitY = Point(0, 1);

Point target_point;

void makeFigures(GameLoop* game_loop);

void checkShot(GameLoop* game_loop);

//int main(void) {//�޸𸮸� �׽�Ʈ��
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//    const wchar_t* a = L"�����â";
//    OutputDebugString(a);
//    Sleep(5000);
//    GameLoop* game_loop = new GameLoop();
//    game_loop->setFPS(12);
//    game_loop->BuildScreen(160, 100, 8, 8);
//    Matrix mat_circle = game_loop->getConsole().makeCircle(10);
//    Object* circle1 = new Object(10, 20); //Object�� �����ϸ� ���������� ���ŵ�.
//    circle1->makeImage(mat_circle);
//    circle1->makeRigidbody();
//    circle1->rigidbody.makeMatrixCollider(mat_circle);
//    circle1->rigidbody.setVelocity(1, 1);
//    delete circle1;
//    return 0;
//}



int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    GameLoop* game_loop = new GameLoop();
    game_loop->setFPS(12);
    game_loop->BuildScreen(160, 100, 8, 8);
    // set pause and resume key to RETURN key
    game_loop->setPauseKey(eag_enter);
    game_loop->setResumeKey(eag_enter);

    //// ���� �׸� �׷����� �� �ʱ�ȭ
    target_point = Point(20, 20);

    Sound my_sound = Sound();
    my_sound.playSound("hello.wav");
    makeFigures(game_loop);
    game_loop->start();
    while (!game_loop->objects.empty()) {
        game_loop->objects.pop_back();
    }
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
    game_loop->getConsole().setTmpBufScreen();


    // �׸� ������ ��� �ʱ�ȭ
    Matrix mat_circle = game_loop->getConsole().makeCircle(10);
    Matrix mat_box = game_loop->getConsole().makeBox(game_loop->getConsole().getScreenWidth(), game_loop->getConsole().getScreenHeight());
    Matrix mat_rect = game_loop->getConsole().makeRect(10, 4);

    //���� �ʱ�ȭ

    Object* circle1 =new Object(target_point.getX(), target_point.getY()); //Object�� �����ϸ� ���������� ���ŵ�.
    circle1->makeImage(mat_circle);
    circle1->makeRigidbody();
    circle1->rigidbody.makeMatrixCollider(mat_circle);
    circle1->rigidbody.setVelocity(1, 1);
 //   circle1->rigidbody.makeMatrixCollider(mat_circle);


    Object* boundary = new Object(0, 0);
    boundary->makeImage(mat_box);
    boundary->makeRigidbody();
    boundary->rigidbody.makeMatrixCollider(mat_box);
    boundary->setName("boundary");

    // �������� vector�� append
    game_loop->objects.push_back(boundary);
    game_loop->objects.push_back(circle1);



    //��� �׸���
    Matrix background = game_loop->getConsole().makeFile2Matrix("C:\\Users\\���Ƽ�\\Desktop\\EAG\\Educational-Ascii-Game-engine\\background");//���� ���
    //Matrix background = game_loop->getConsole().makeFile2Matrix("C:\\Users\\andre\\Desktop\\fps\\Educational-Ascii-Game-engine\\background");
    // ����
    //Matrix background = getConsole().makeFile2Matrix("C:\\Users\\ilove\\source\\repos\\Educational-Ascii-Game-engine\\background");//���� ���
    game_loop->getConsole().drawMatrix(0, 0, background);

    //player object
    Object* player = new Object(30, 60);
    Matrix plane1 = game_loop->getConsole().makeFile2Matrix("C:\\Users\\���Ƽ�\\Desktop\\EAG\\Educational-Ascii-Game-engine\\plane");
    //Matrix plane1 = game_loop->getConsole().makeFile2Matrix("C:\\Users\\andre\\Desktop\\fps\\Educational-Ascii-Game-engine\\plane");
    // ���� 
    //Matrix matrix1 = getConsole().makeFile2Matrix("C:\\Users\\ilove\\source\\repos\\Educational-Ascii-Game-engine\\plane");
    player->makeRigidbody();
    player->makeImage(plane1);
    player->rigidbody.makeMatrixCollider(plane1);
    player->setName("player");
    game_loop->objects.push_back(player);

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

/*
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
*/