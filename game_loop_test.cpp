#include "game_loop.h"

class TestGame : public GameLoop {

private:
    vector<Matrix> MV_;  // enemy �׸� ����
    Sound sound_;
    clock_t last_time_;
    
    vector <Object*> enemys;
    vector <Object*> bullets;
    Object* player0;
    Object* boundary0;

    int life_;
    int score_;

    void initialize() override;
    void updateLoop() override;

    void checkKey() override;
    void checkMove(Object& obj);
    void checkShoot(vector<Object*>& objects, Object& player);
    void Move_Collision_Check();
    void makeEnemy();
    void drawLife();
    //void minuslife();
    //void addlife();
    void addscore(int _score);

public:
    TestGame();
    Sound getSound();
};
TestGame::TestGame()
{
    sound_ = Sound();
    life_ = 5;
    score_ = 0;
}
void TestGame::initialize()
{

    // �׸� ������ ��� �ʱ�ȭ

    Matrix mat_box = getConsole().makeBox(getConsole().getScreenWidth(),getConsole().getScreenHeight());
    Matrix mat_rect = getConsole().makeRect(10, 4);

    //���� �ʱ�ȭ

    boundary0 = new Object(0, 0);
    boundary0->makeImage(mat_box);
    boundary0->makeRigidbody();
    boundary0->rigidbody.makeMatrixCollider(mat_box);
    boundary0->setName("boundary");

    // �������� vector�� append
    enemys.push_back(boundary0);//enemy���� ����
    bullets.push_back(boundary0);

    //��� �׸���
    Matrix background = getConsole().makeFile2Matrix("./usrlib/background");
    getConsole().drawMatrix(0, 0, background);

    //player object
    player0 = new Object(30, 60);
    Matrix plane1 = getConsole().makeFile2Matrix("./usrlib/plane");
    player0->makeRigidbody();
    player0->makeImage(plane1);
    player0->rigidbody.makeMatrixCollider(plane1);
    player0->setName("player");
    bullets.push_back(player0);

    //enemy �׸� ����
    Matrix M1 = getConsole().makeFile2Matrix("./usrlib/enemy1");
    Matrix M2 = getConsole().makeFile2Matrix("./usrlib/enemy2");
    Matrix M3 = getConsole().makeFile2Matrix("./usrlib/enemy3");
    MV_.push_back(M1);
    MV_.push_back(M2);
    MV_.push_back(M3);

    last_time_ = clock();//last_time_ �ð�üũ��
}
void TestGame::checkKey()
{
   // Object* player = objects[0]->findByName(objects, "player");
    checkMove(*player0);
    checkShoot(bullets, *player0);
}
void TestGame::updateLoop()
{
    clock_t start;

    start = clock();                 // start timer

    if ((start - last_time_) > 1000) {//when passed make enemy
        makeEnemy();
        last_time_ = start;
    }

//�浹üũ�� ����
    Move_Collision_Check();
    getConsole().drawTmpObjects(enemys);
    getConsole().drawTmpObjects(bullets);
    getConsole().drawTmpObject(*player0);
    drawLife();
}


void TestGame::Move_Collision_Check() {


    for (int i = 0; i < enemys.size(); i++)  enemys[i]->move(bullets); 
    for (int i = 0; i < bullets.size(); i++)  bullets[i]->move(enemys); //���� �÷��̾ ����
    
    boundary0->collision_flg = 0;

    if (player0->collision_flg) {
        if (life_ > 0)  life_--; //ü�� ����
        if (life_ <= 0) exit();
        player0->collision_flg = 0;
    }
    for (int j = 0; j < bullets.size(); j++) {
        if (bullets[j]->collision_flg) {
            delete bullets[j];
            bullets.erase(bullets.begin() + j);
        }
    }
    for (int j = 0; j < enemys.size(); j++) {
        if (enemys[j]->collision_flg) {
            delete enemys[j];
            enemys.erase(enemys.begin() + j);
            addscore(10);
        }
    }

 
}



Sound TestGame::getSound()
{
    return sound_;
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
 // �ð��� ���� enemy �߻�
void TestGame::makeEnemy()
{ 
    int rand_num = rand();
    Object* enemy = new Object(140 / (rand_num % 4 + 1), 2);
    enemy->makeImage(MV_[rand_num % 3]); //��� 3��
    enemy->makeRigidbody();
    enemy->rigidbody.makeMatrixCollider(MV_[rand_num % 3]);
    enemy->setName("enemy");
    enemy->rigidbody.setVelocity((rand_num % 4 - 2), rand_num % 3 + 1);
    enemys.push_back(enemy);
}

void TestGame::drawLife()
{
    for (int i = 0; i < life_; i++) {
        getConsole().drawTmp(2*i + 2, 2, L'��', FG_RED);
        getConsole().drawTmp(2*i + 3, 2, L' ', FG_RED);
    }
    //Matrix life_image;
    //life_image.width = 10;
    //life_image.height = 1;
    //life_image.color = new unsigned char[1 * 10];
    //for (int i = 0; i < 10; i++)
    //{
    //    life_image.color[i] = FG_RED;
    //}
    //life_image.element = new short* [1];
    //for (int i = 0; i < 1; i++)
    //{
    //    life_image.element[i] = new short[10];
    //}
    //for (int i = 0; i < 5; i++)
    //{
    //    life_image.element[0][2 * i] = L'��';
    //    life_image.element[0][2 * i + 1] = L' ';
    //}
    //getConsole().drawMatrix(5, 2, life_image);
}
//
//void TestGame::minuslife()
//{
//    Matrix null_image;
//    null_image.width = 1;
//    null_image.height = 1;
//    null_image.color = new unsigned char[1];
//    null_image.color[0] = FG_BLACK;
//    null_image.element = new short* [1];
//    null_image.element[0] = new short[1];
//    null_image.element[0][0] = L'��';
//    if (life_ > 0)
//    {
//        getConsole().drawMatrix(3 + life_ * 2, 2, null_image);
//        life_--;
//    }
//    else
//    {
//        exit();
//    }
//}

//void TestGame::addlife()
//{
//    for (int i = 0; i < life_; i++) {
//        getConsole().drawTmp(i + 2, 2, L'��', FG_RED);
//    }
    //Matrix null_image;
    //null_image.width = 1;
    //null_image.height = 1;
    //null_image.color = new unsigned char[1];
    //null_image.color[0] = FG_RED;
    //null_image.element = new short* [1];
    //null_image.element[0] = new short[1];
    //null_image.element[0][0] = L'��';
    //if (life_ < 5)
    //{
    //    getConsole().drawMatrix(5 + life_ * 2, 2, null_image);
    //    life_++;
    //}
//}

void TestGame::addscore(int _score)
{
    this->score_ = this->score_ + _score;
    int temp = this->score_;
    Matrix score_image;
    score_image.width = 20;
    score_image.height = 1;
    score_image.color = new unsigned char[20];
    for (int i = 0; i < 20; i++)
    {
        score_image.color[i] = FG_WHITE;
    }
    score_image.element = new short* [1];
    score_image.element[0] = new short[20];
    for (int i = 0; i < 20; i++)
    {
        score_image.element[0][19 - i] = L'0' + temp % 10;
        temp = temp / 10;
    }
    getConsole().drawMatrix(40, 2, score_image);
}

Point g_target_point;

void makeFigures(TestGame* test_game);

int main(void)
{

    TestGame* test_game = new TestGame();
    test_game->setFPS(12);
    test_game->buildScreen(160, 100, 8, 8);
    // set pause and resume key to RETURN key
    test_game->setPauseKey(EAG_VKEY_RETURN);
    test_game->setResumeKey(EAG_VKEY_RETURN);

    //// ���� �׸� �׷����� �� �ʱ�ȭ

    test_game->start();
    return 0;
}

void makeFigures(TestGame* test_game)
{
}
