#include "game_loop.h"

extern KeyListener klc;

GameLoop::GameLoop()
{
    fps_ = 30;
    is_pause_ = false;
    is_gameover_ = false;
    key_pause_ = EOF;
    key_resume_ = EOF;
    console_ = Console();
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

// 임시 함수, 나중에 제거 예정
void GameLoop::initialize()
{
    //경로 알아서 지정
    Matrix M1 = console_.makeFile2Matrix("C:\\Users\\정훈석\\Desktop\\EAG\\Educational-Ascii-Game-engine\\enemy1");
    Matrix M2 = console_.makeFile2Matrix("C:\\Users\\정훈석\\Desktop\\EAG\\Educational-Ascii-Game-engine\\enemy2");
    Matrix M3 = console_.makeFile2Matrix("C:\\Users\\정훈석\\Desktop\\EAG\\Educational-Ascii-Game-engine\\enemy3");
    MV.push_back(M1);
    MV.push_back(M2);
    MV.push_back(M3);
}

/* Set frame per second. Default FPS is 30. */
void GameLoop::setFPS(double _frames)
{
    fps_ = _frames;
}

void GameLoop::start()
{
    clock_t start, end, interval, remaining_time;
    bool gameover = 0;
    initialize();

    int last_time = clock();

    while (!is_gameover_) {
        vCheckPause();
        start = clock();                 // start timer

        if ((start - last_time) > 1000) {//when passed make enemy
            makeEnemy();
            last_time = start;
        }

        update();
        end = clock();                // end timer

        interval = end - start;    // total elapsed time during a iteration
        remaining_time = vGetUnitTime() - interval;             // remaining time to sleep

        Sleep(remaining_time);
    }
}


void GameLoop::update()
{
    //Object* player = objects[0]->findByName(objects, "player");

    checkKey(objects);
    string a= to_string(objects.size())+"\n";
    console_.print(a,2,2);
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->move(objects);
    }
    // move according to velocity
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->collision_flg) { //충돌한 적이 있으면 collision_flg
            if (objects[i]->getName()) {
                if (strcmp(objects[i]->getName(), "boundary")&& strcmp(objects[i]->getName(), "player")) {//boundary 경계가 아니면 삭제한다.
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
    console_.setTmpBufScreen();
    console_.drawTmpObjects(objects);
    console_.update();

}

/* If key_pause_ is pressed, pause game loop. */
void GameLoop::vCheckPause()
{
    if (GetAsyncKeyState(klc.eagKeyToVK(key_pause_)))
        vCheckResume();
}

void GameLoop::vCheckResume()
{
    Sleep(100);
    while (true) {
        if (GetAsyncKeyState(klc.eagKeyToVK(key_resume_)) & 0x8000) {
            klc.reset();
            return;
        }
    }
}

void GameLoop::setPauseKey(int key)
{
    key_pause_ = key;
}

void GameLoop::setResumeKey(int key)
{
    key_resume_ = key;
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
    else if (klc.keycheck(eag_ctrl)) { //ctrl키 멈추기
        exitLoop();
    }
    else {
        obj.rigidbody.setVelocity(0, 0);
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

void GameLoop::makeEnemy() { //적발생

    int rand_num = rand();
    Object* enemy = new Object(140 / (rand_num % 4 + 1), 2);
    enemy->makeImage(MV[rand_num % 3]); //모양 3개
    enemy->makeRigidbody();
    enemy->rigidbody.makeMatrixCollider(MV[rand_num % 3]);
    enemy->setName("enemy");
    enemy->rigidbody.setVelocity((rand_num % 4 - 2), rand_num % 3 + 1);
    objects.push_back(enemy);
}

