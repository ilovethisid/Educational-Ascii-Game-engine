

#include <cstdlib>  // system()을 위한 헤더 파일



#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>//메모리 누수

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#include "game_loop.h"

//int main(void) {//메모리릭 테스트용
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//    const wchar_t* a = L"디버그창";
//    OutputDebugString(a);
//    Sleep(5000);
//    GameLoop* game_loop = new GameLoop();
//    game_loop->setFPS(12);
//    game_loop->BuildScreen(160, 100, 8, 8);
//    Matrix mat_circle = game_loop->getConsole().makeCircle(10);
//    Object* circle1 = new Object(10, 20); //Object로 선언하면 지역변수라 제거됨.
//    circle1->makeImage(mat_circle);
//    circle1->makeRigidbody();
//    circle1->rigidbody.makeMatrixCollider(mat_circle);
//    circle1->rigidbody.setVelocity(1, 1);
//    delete circle1;
//    return 0;
//}

class TestGame : public GameLoop {

private:
    vector<Matrix> MV_;  // enemy 그림 벡터
    Sound sound_;
    clock_t last_time_;

    void initialize() override;
    void updateLoop() override;

    void checkKey() override;
    void checkMove(Object& obj);
    void checkShoot(vector<Object*>& objects, Object& player);

    void makeEnemy();

public:
    TestGame();
    Sound getSound();
};
TestGame::TestGame()
{
    sound_ = Sound();
}
void TestGame::initialize()
{

    last_time_ = clock();

    Matrix M1 = getConsole().makeFile2Matrix("./usrlib/enemy1");
    Matrix M2 = getConsole().makeFile2Matrix("./usrlib/enemy2");
    Matrix M3 = getConsole().makeFile2Matrix("./usrlib/enemy3");
    MV_.push_back(M1);
    MV_.push_back(M2);
    MV_.push_back(M3);
}
void TestGame::checkKey()
{
    Object* player = objects[0]->findByName(objects, "player");
    checkMove(*player);
    checkShoot(objects, *player);
}
void TestGame::updateLoop()
{
    clock_t start;

    start = clock();                 // start timer

    if ((start - last_time_) > 1000) {//when passed make enemy
        makeEnemy();
        last_time_ = start;
    }

    string a = to_string(objects.size()) + "\n";
    getConsole().print(a, 2, 2);
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->move(objects);
    }
    // move according to velocity
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->collision_flg) { //충돌한 적이 있으면 collision_flg
            if (objects[i]->getName()) {
                if (strcmp(objects[i]->getName(), "boundary") && strcmp(objects[i]->getName(), "player")) {//boundary 경계가 아니면 삭제한다.
                    delete objects[i];
                    objects.erase(objects.begin() + i);
                    i--;
                }
            }
            else { //null이면
                delete objects[i];
                objects.erase(objects.begin() + i);
                i--;
            }
        }
    }
}
// Implementation of KeyListener
void TestGame::checkMove(Object& obj)
{
    if (getKeyListener().keycheck(EAG_VKEY_UP)) {
        obj.rigidbody.setVelocity(0, -2);
        if (getKeyListener().keycheck(EAG_VKEY_LEFT))
            obj.rigidbody.setVelocity(-2, -2);
        else if (getKeyListener().keycheck(EAG_VKEY_RIGHT))
            obj.rigidbody.setVelocity(2, -2);
    }
    else if (getKeyListener().keycheck(EAG_VKEY_DOWN)) {
        obj.rigidbody.setVelocity(0, 2);
        if (getKeyListener().keycheck(EAG_VKEY_LEFT))
            obj.rigidbody.setVelocity(-2, 2);
        else if (getKeyListener().keycheck(EAG_VKEY_RIGHT))
            obj.rigidbody.setVelocity(2, 2);
    }
    else if (getKeyListener().keycheck(EAG_VKEY_LEFT)) {
        obj.rigidbody.setVelocity(-2, 0);
    }
    else if (getKeyListener().keycheck(EAG_VKEY_RIGHT)) {
        obj.rigidbody.setVelocity(2, 0);
    }
    else if (getKeyListener().keycheck(EAG_VKEY_ESC)) { // press ESC key to exit loop
        exit();
    }
    else {
        obj.rigidbody.setVelocity(0, 0);
    }
}
void TestGame::checkShoot(vector<Object*>& objects, Object& player)
{
    if (getKeyListener().keycheck(EAG_VKEY_SPACE)) {
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
        sound_.playSound("./usrlib/laser-gun.wav");
    }
}
 //시간에 따라 enemy 발생
void TestGame::makeEnemy()
{ 
    int rand_num = rand();
    Object* enemy = new Object(140 / (rand_num % 4 + 1), 2);
    enemy->makeImage(MV_[rand_num % 3]); //모양 3개
    enemy->makeRigidbody();
    enemy->rigidbody.makeMatrixCollider(MV_[rand_num % 3]);
    enemy->setName("enemy");
    enemy->rigidbody.setVelocity((rand_num % 4 - 2), rand_num % 3 + 1);
    objects.push_back(enemy);
}
Sound TestGame::getSound()
{
    return sound_;
}

Point g_target_point;

void makeFigures(TestGame* test_game);

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    TestGame* test_game = new TestGame();
    test_game->setFPS(12);
    test_game->buildScreen(160, 100, 8, 8);
    // set pause and resume key to RETURN key
    test_game->setPauseKey(EAG_VKEY_RETURN);
    test_game->setResumeKey(EAG_VKEY_RETURN);

    //// 최초 그림 그려지는 점 초기화
    g_target_point = Point(20, 20);

    makeFigures(test_game);
    test_game->start();
    while (!test_game->objects.empty()) {
        test_game->objects.pop_back();
    }

    return 0;
}

void makeFigures(TestGame* test_game)
{
    test_game->getConsole().setTmpBufScreen();


    // 그릴 도형의 행렬 초기화
    Matrix mat_circle = test_game->getConsole().makeCircle(10);
    Matrix mat_box = test_game->getConsole().makeBox(test_game->getConsole().getScreenWidth(), test_game->getConsole().getScreenHeight());
    Matrix mat_rect = test_game->getConsole().makeRect(10, 4);

    //도형 초기화

    Object* circle1 =new Object(g_target_point.getX(), g_target_point.getY()); //Object로 선언하면 지역변수라 제거됨.
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

    // 도형들을 vector에 append
    test_game->objects.push_back(boundary);
    test_game->objects.push_back(circle1);



    //배경 그리기
    Matrix background = test_game->getConsole().makeFile2Matrix("./usrlib/background");
    test_game->getConsole().drawMatrix(0, 0, background);

    //player object
    Object* player = new Object(30, 60);
    Matrix plane1 = test_game->getConsole().makeFile2Matrix("./usrlib/plane");
    player->makeRigidbody();
    player->makeImage(plane1);
    player->rigidbody.makeMatrixCollider(plane1);
    player->setName("player");
    test_game->objects.push_back(player);

}
