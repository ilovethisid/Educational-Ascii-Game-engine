
#define _CRT_SECURE_NO_WARNINGS

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 70
#define BOSS_SCORE 500
#define BOSS_LIFE 120
#include <thread>

#include "game_loop.h"



class TestGame : public GameLoop {

private:
    vector<Matrix> enemy_images;  // enemy 그림 벡터
    vector<Matrix> bullet_images;
    Sound sound_;
    clock_t last_time_; 
    vector <Object*> enemys;
    vector <Object*> bullets;
    vector <Object*> enemy_bullets;
    Object* player0;
    Object* boundary0;
    thread th_sound;
    

    class Enemy :public Object {
    public:
        char life = 1;
        boolean shoot_flg = false;
        char bullet_frame_num = 0;
        Enemy(int x, int y, int v_x, int v_y, int type, Matrix& image,Matrix& collider);
        virtual ~Enemy() {};
        void virtual shoot(Matrix& image, vector<Object*>& enemy_bullets);
        void virtual event(Console& console) {};
    };

    class Boss :public Enemy{
    public:
        char shoot_pattern;
        char* boss_flg;
        Boss(int x, int y, int v_x, int v_y, int type ,char* boss_flg, Matrix& image, Matrix& collider);
        ~Boss();
        void shoot(Matrix& image, vector<Object*>& enemy_bullets);
        void event(Console& console);
    };



    int life_;
    int score_;
    char boss_flg=1;
    int scoreboard_[10];
    string namelist[10];
    string user_name_;

    
    void initialize() override;
    void updateLoop() override;

    void checkKey() override;
    void checkMove(Object& obj);
    void checkShoot(vector<Object*>& objects, Object& player);
    void collisionEvent();
    void makeEnemy();
    void drawLife();
    //void minuslife();
    //void addlife();
    void addscore(int _score);
    void showscore(int _score);
    void showscoreboard();
    void addscoreboard();
    void loadscoreboard();
    void savescoreboard();
    void dieEvent();
    static void makeBullet(int x, int y, int v_x, int v_y, Matrix& image, vector<Object*>& kind_bullets);
  

public:
    void startMenu();
    void endEvent();
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
    //enemy_images matrix
    enemy_images.push_back(makeFile2Matrix("./usrlib/enemy1"));
    enemy_images.push_back(makeFile2Matrix("./usrlib/enemy2"));
    enemy_images.push_back(makeFile2Matrix("./usrlib/enemy3"));
    enemy_images.push_back(makeFile2Matrix("./usrlib/boss"));
    enemy_images.push_back(makeFile2Matrix("./usrlib/boss_collider"));
    //bullet_images matrix
    bullet_images.push_back(Matrix(1, 1, (short*)L"|", FG_YELLOW));
    bullet_images.push_back(Matrix(2, 1, (short*)L"◈ ", FG_RED));
    bullet_images.push_back(Matrix(1, 1, (short*)L"● ", FG_RED));

    // 그릴 도형의 행렬 초기화
    Matrix mat_box = makeBox(getConsole().getScreenWidth(),getConsole().getScreenHeight(),2);
    Matrix mat_rect = makeRect(10, 4);

    //도형 초기화

    boundary0 = new Object(0, 0);
    boundary0->makeImage(mat_box);
    boundary0->makeRigidbody();
    boundary0->rigidbody.makeMatrixCollider(mat_box);
    boundary0->setName("boundary");
    objects.push_back(boundary0);

    // 도형들을 vector에 append
    //enemys.push_back(boundary0);//enemy에서 관리
    //bullets.push_back(boundary0);

    //배경 그리기
    Matrix background = makeFile2Matrix("./usrlib/background");
    getConsole().drawMatrix(0, 0, background);

    // show score
    showscore(score_);

    //player object
    player0 = new Object(30, 60);
    Matrix plane1 =makeFile2Matrix("./usrlib/plane");
    player0->makeRigidbody();
    player0->makeImage(plane1);
    player0->rigidbody.makeMatrixCollider(plane1);
    player0->setName("player");
    //bullets.push_back(player0);
    objects.push_back(player0);
    last_time_ = clock();//last_time_ 시간체크용

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
    static int spawn_interval = (int)fps_;
    // spawn interval in frames
    // spawn interval is 1 sec at start
    static int count_frames = 0;

    int score_interval = (int)fps_ / 4;

    start = clock();                 // start timer

    //if ((start - last_time_) > spawn_interval) { //when passed make enemy
    //    makeEnemy();
    //    last_time_ = start;
    //}

    if (count_frames % spawn_interval == 0) {
        makeEnemy();
    }

    if (count_frames % score_interval == 0) {
        addscore(1);
    }

    if (count_frames % ((int)fps_ * 3) == 0) {
        if (spawn_interval > (int)fps_ / 2) {
            spawn_interval--;
            //sound_.playSound2("./../usrlib/laser-gun.wav");
        }
    }

   

//충돌체크와 판정
    collisionEvent();
    getConsole().drawTmpObjects(enemys);
    getConsole().drawTmpObjects(bullets);
    getConsole().drawTmpObjects(enemy_bullets);
    getConsole().drawTmpObject(*player0);
    drawLife();
    count_frames++;
}

void TestGame::dieEvent() {
    exit();
}
void TestGame::endEvent() {
    getConsole().clearTmpBufScreen();
    if (boss_flg==2){
        Matrix tmp = makeFile2Matrix("./usrlib/game_clear");
        getConsole().drawMatrix(35, 10, tmp);
    }
    else  {
        Matrix die = makeFile2Matrix("./usrlib/die_message");
        getConsole().drawMatrix(30, 10, die);
    }

    loadscoreboard();
    addscoreboard();
    savescoreboard();
    showscoreboard();
    getConsole().print("press esc to exit", 50, 5);

    getConsole().setTmpBufScreen();
    getConsole().update();
    getKeyListener().reset();
    while (!getKeyListener().keycheck(EAG_VKEY_ESC));
}



void TestGame::collisionEvent() {

    player0->collision_flg = 0;

    for (int i = 0; i < enemys.size(); i++) { //enemys-> 벽&플레이어
        enemys[i]->move(objects);
    }
    for (int i = 0; i < enemy_bullets.size(); i++)  enemy_bullets[i]->move(objects);

    for (int i = 0; i < bullets.size(); i++)  bullets[i]->move(enemys); //총알->enemys


    player0->move(objects); //플레이어와 벽
    boundary0->collision_flg = 0;




    //if (player0->collision_flg==1) {
    //    for (int i = 0; i < enemys.size(); i++) {
    //        if (enemys[i]->collision_flg == 1) {
    //            if (life_ > 0)  life_--; //체력 감소
    //            if (life_ <= 0) exit();
    //        }
    //    }
    //}

    /* 동진 - collision에서 colliding하는 object 반환(getCollidingObjects) */
    // collision with enemy
    vector<Object*> player_colliding_objects = player0->getCollidingObjects(enemys);

    if (player_colliding_objects.size() >= 1) {
        getConsole().print(to_string(player_colliding_objects.size()),1,1);
        for (int i = 0; i < player_colliding_objects.size(); i++) {
            if (life_ > 0)  life_--; //체력 감소
            if (life_ <= 0)
            {
                dieEvent();
            }
        }
    }

    for (int i = 0; i < player_colliding_objects.size(); i++) {
        player_colliding_objects.pop_back();
    }
    // free memory

    //collision with enemy bullets
    vector<Object*> player_colliding_objects0 = player0->getCollidingObjects(enemy_bullets);

    if (player_colliding_objects0.size() >= 1) {
        getConsole().print(to_string(player_colliding_objects0.size()), 1, 1);
        for (int i = 0; i < player_colliding_objects0.size(); i++) {
            if (life_ > 0)  life_--; //체력 감소
            if (life_ <= 0)
            {
                dieEvent();
            }
        }
    }

    for (int i = 0; i < player_colliding_objects0.size(); i++) {
        player_colliding_objects0.pop_back();
    }




    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i]->getCollidingObjects(enemys).size() >= 1) {
            addscore(10);
        }
    }

    player0->collision_flg = 0;

    for (int j = 0; j < bullets.size(); ) {
        if (bullets[j]->collision_flg) {
            delete bullets[j];
            bullets.erase(bullets.begin() + j);

        }
        else j++;
    }

    for (int j = 0; j < enemys.size();) {
        Enemy* tmp = (Enemy*)enemys[j];
        tmp->event(getConsole());

        if (tmp->shoot_flg) tmp->shoot(bullet_images[1], enemy_bullets);

        if (tmp->collision_flg) {
            tmp->life--;
            if ((tmp->life) <= 0) {
                delete tmp;
                enemys.erase(enemys.begin() + j);
            }
            else
               j++;
            tmp->collision_flg = 0;
        }
        else j++;
    }

    for (int j = 0; j < enemy_bullets.size();) {
        if (enemy_bullets[j]->collision_flg) {
            delete enemy_bullets[j];
            enemy_bullets.erase(enemy_bullets.begin() + j);
            //addscore(10);
        }
        else j++;
    }
    if (boss_flg == 2) {
        exit();
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


void TestGame::checkShoot(vector<Object*>& bullets, Object& player)
{
    if (getKeyListener().keycheck(EAG_VKEY_SPACE)) {
        makeBullet(player.getX() + player.getImage().width / 2, player.getY() - 2,  0, -3,bullet_images[0],bullets);

        sound_.playSound("./../usrlib/laser-gun.wav");
    }
}




 // 시간에 따라 enemy 발생
void TestGame::makeEnemy()
{ 
    int rand_num = rand();
    int type = rand_num % 3;
    Object* enemy = new Enemy(SCREEN_WIDTH / 8 * (rand_num % 5 + 2), 2, rand_num % 4 - 2, type + 1,type,enemy_images[type], enemy_images[type]);
    enemys.push_back(enemy);

    if (score_ > BOSS_SCORE  && (boss_flg == 1)) {
        Object* enemy = new Boss(30, 4, 0, 0, 3,&boss_flg ,enemy_images[3], enemy_images[3]);
        enemys.push_back(enemy);
        boss_flg = 0;
    }

}


void TestGame::drawLife()
{
    //getConsole().print(to_string(life_),1,1);
    for (int i = 0; i < life_; i++) {
        getConsole().drawTmp(2*i + 3, 3, L'♥', FG_RED);
        getConsole().drawTmp(2*i + 4, 3, L' ', FG_RED);
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
    //    life_image.element[0][2 * i] = L'♥';
    //    life_image.element[0][2 * i + 1] = L' ';
    //}
    //getConsole().drawMatrix(5, 2, life_image);
}


void TestGame::addscore(int _score)
{
    this->score_ = this->score_ + _score;
    showscore(this->score_);

}

void TestGame::showscore(int _score)
{
    char score_text[20];
    snprintf(score_text, 20, "score: %d", _score);
    getConsole().print(score_text,3,23);
}


TestGame::Enemy::Enemy(int x, int y, int v_x, int v_y, int type, Matrix& image, Matrix& collider) :Object(x, y) {
    makeImage(image);
    makeRigidbody();
    rigidbody.makeMatrixCollider(collider);
    rigidbody.setVelocity(v_x, v_y);
    if (type == 0) shoot_flg = true;
}

void TestGame::Enemy::shoot(Matrix& image, vector<Object*>& enemy_bullets) {

    if (bullet_frame_num > 12) {
        makeBullet(getX() + getImage().width / 2, getY() + getImage().height + 1, 0, 3, image, enemy_bullets);
        bullet_frame_num = 0;
        //Object* ebullet;
        //ebullet = new Object(getX() + getImage().width / 2, getY() + getImage().height + 1);
        //Matrix image = Matrix(2, 1);
        //image.element[0][0] = L'◈';
        //image.element[0][1] = ' ';
        //ebullet->makeImage(image);
        //ebullet->getImage().setColor(FG_RED);
        //ebullet->makeRigidbody();
        //ebullet->rigidbody.makeMatrixCollider(image);
        //ebullet->setName("bullet");
        //ebullet->rigidbody.setVelocity(0, 3);
        //enemy_bullets.push_back(ebullet);
        //          sound_.playSound("./usrlib/laser-gun.wav");

    }
    else
        bullet_frame_num++;
    
    
}

TestGame::Boss::Boss(int x, int y, int v_x, int v_y, int type, char* boss_pnt, Matrix& image,Matrix& collider) :Enemy( x,  y,  v_x,  v_y,  type, image, collider) {
    boss_flg = boss_pnt;
    shoot_flg = true;
    shoot_pattern = 0;
    life = BOSS_LIFE;
}
TestGame::Boss::~Boss() {
    *boss_flg = 2;
}
void TestGame::Boss::shoot(Matrix& image, vector<Object*>& enemy_bullets) {
    if (bullet_frame_num > 12) {
        if (shoot_pattern == 0) {
            int x = getX();
            int y = getY();
            makeBullet(x + 2, 7, 0, 3, image, enemy_bullets);
            makeBullet(x + 9, 7, 0, 3, image, enemy_bullets);
            makeBullet(x + 19, 14, 0, 5, image, enemy_bullets);
            makeBullet(x + 31, 7, 0, 3, image, enemy_bullets);
            makeBullet(x + 38, 7, 0, 3, image, enemy_bullets);
            bullet_frame_num = 0;
        }
        //Object* ebullet;
        //ebullet = new Object(getX() + getImage().width / 2, getY() + getImage().height + 1);
        //Matrix image = Matrix(2, 1);
        //image.element[0][0] = L'◈';
        //image.element[0][1] = ' ';
        //ebullet->makeImage(image);
        //ebullet->getImage().setColor(FG_RED);
        //ebullet->makeRigidbody();
        //ebullet->rigidbody.makeMatrixCollider(image);
        //ebullet->setName("bullet");
        //ebullet->rigidbody.setVelocity(0, 3);
        //enemy_bullets.push_back(ebullet);
        //          sound_.playSound("./usrlib/laser-gun.wav");

    }
    else
        bullet_frame_num++;
}

void TestGame::Boss::event(Console& console) {
    int x = getX();
    for (int i = 0; i < life; i++) {
        console.drawTmp( x+i-30, 2, L'■', FG_RED);
    }
}

void TestGame::makeBullet(int x,int y,int v_x,int v_y,Matrix& image,vector<Object*>& kind_bullets) {
    Object* bullet;
    bullet = new Object(x, y);
    bullet->makeImage(image);
    bullet->makeRigidbody();
    bullet->rigidbody.makeMatrixCollider(image);
    bullet->rigidbody.setVelocity(v_x, v_y);
    kind_bullets.push_back(bullet);
}

void TestGame::showscoreboard()
{
    int board_x = 10;
    int board_y = 10;
    getConsole().print("score board", board_y, board_x);
    getConsole().drawBox(board_x-1,board_y-1,23,30,1,'*');
    //getConsole().print(/*"┌"*/"*", board_y - 1, board_x - 1);
    //getConsole().print(/*"┐"*/"*", board_y - 1, board_x - 1 + 15);
    //getConsole().print(/*"┘"*/"*", board_y - 1 + 30, board_x - 1 + 15);
    //getConsole().print(/*"└"*/"*", board_y - 1 + 30, board_x - 1);
    //for (int i = 1; i < 15; i++)
    //{
    //    getConsole().print(/*"─"*/"*", board_y - 1, board_x - 1 + i);
    //    getConsole().print(/*"─"*/"*", board_y - 1 + 30, board_x - 1 + i);
    //}
    //for (int i = 1; i < 30; i++)
    //{
    //    getConsole().print(/*"│"*/"*", board_y - 1 + i, board_x - 1);
    //    getConsole().print(/*"│"*/"*", board_y - 1 + i, board_x - 1 + 15);
    //}
    for (int i = 0; i < 10; i++)
    {
        char score_text[20];
        snprintf(score_text, 20, "%3d. %s: %d", i + 1, namelist[i].c_str(), scoreboard_[i]); puts(score_text);
        getConsole().print(score_text, board_y + i * 2 + 2, board_x);
    }
    getConsole().setTmpBufScreen();
    getConsole().update();
}
void TestGame::loadscoreboard()
{
    ifstream in("./usrlib/scoreboard.csv");
    string in_line;
            getline(in, in_line, '\n');
    if (in.is_open())
    {
        for (int i = 0; i < 10; i++)
        {
            getline(in, in_line, ',');
            scoreboard_[i] = stoi(in_line);
            getline(in, in_line, '\n');
            namelist[i] = in_line;
        }
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            scoreboard_[i] = 0;
            namelist[i] = "AAAA";
        }
    }
    in.close();
}
void TestGame::addscoreboard()
{
    getConsole().print("Type your name : ", 5, 6);
    // get the name of player
    getConsole().print("press Enter", 40, 10);
    GotoXY(Point(25, 5));
    getConsole().setTmpBufScreen();
    getConsole().update();
    char temp[10]; 
    scanf("%s", temp);
    user_name_ = temp;
    for (int i = 0; i < 10; i++)
    {
        if (score_ > scoreboard_[i])
        {
            int temp = scoreboard_[i];
            string temp_name = namelist[i];
            scoreboard_[i] = score_;
            namelist[i] = user_name_;
            i++;
            for (i; i < 10; i++)
            {
                int temp2 = scoreboard_[i];
                string temp2_name = namelist[i];
                scoreboard_[i] = temp;
                namelist[i] = temp_name;
                temp = temp2;
                temp_name = temp2_name;
            }
        }
    }
}
void TestGame::savescoreboard()
{
    ofstream out("./usrlib/scoreboard.csv");
    string out_line;

    out << "temp" << '\n';
    for (int i = 0; i < 10; i++)
    {
        out << scoreboard_[i] << ',';
        out << namelist[i] << '\n';
    }
    out.close();
}
void TestGame::startMenu()
{
    getKeyListener().reset();
    Matrix title = makeFile2Matrix("./usrlib/title");
    Matrix start_button = makeFile2Matrix("./usrlib/start_button");
    Matrix score_button = makeFile2Matrix("./usrlib/score_button");
    int select = -1;
    getConsole().clearTmpBufScreen();
    getConsole().drawMatrix(10, 10, title);
    getConsole().drawMatrix(10, 50, start_button);
    getConsole().drawMatrix(50, 50, score_button);
    getConsole().print("press space to select", 40, 80);
    getConsole().setTmpBufScreen();
    getConsole().update();
    start_button.setColor(FG_YELLOW);
    score_button.setColor(FG_YELLOW);
    getKeyListener().keycheck(EAG_VKEY_SPACE);
    getConsole().setTmpBufScreen();
    getConsole().drawTmpMatrix(10, 50, start_button);
    getConsole().update();
    select = 0;
    while (!getKeyListener().keycheck(EAG_VKEY_SPACE)) {
        getKeyListener().keycheck(EAG_VKEY_RETURN);
        if (getKeyListener().keycheck(EAG_VKEY_LEFT)) {
            getConsole().setTmpBufScreen(); 
            getConsole().drawTmpMatrix(10, 50, start_button);
            getConsole().update();
            select=0;
        }
        else if (getKeyListener().keycheck(EAG_VKEY_RIGHT)) {
            getConsole().setTmpBufScreen();
            getConsole().drawTmpMatrix(50, 50, score_button);
            getConsole().update();
            select=1;
        }

    }

    getConsole().clearTmpBufScreen();
    if (select == 0) { 
        life_ = 5;
        start(); 
    }
    else if (select == 1) {
        loadscoreboard();
        showscoreboard();
        while (!getKeyListener().keycheck(EAG_VKEY_SPACE));
        Sleep(1000);
        startMenu();
    }
   
  
}


Point g_target_point;



int main(void)
{

    TestGame* test_game = new TestGame();
    test_game->setFPS(12);
    test_game->buildScreen(SCREEN_WIDTH, SCREEN_HEIGHT, 11, 11);
    // set pause and resume key to RETURN key
    test_game->setPauseKey(EAG_VKEY_RETURN);
    test_game->setResumeKey(EAG_VKEY_RETURN);

    

    //// 최초 그림 그려지는 점 초기화
    test_game->startMenu();
    test_game->endEvent();
    return 0;
}


