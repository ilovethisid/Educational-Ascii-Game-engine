#include <iostream>

#include "GraphicEngine.h"
#include "../game_loop.h"

using namespace std;
extern KeyListener klc;

int main(void) {
    //gameloop_t test;
    //test.start();
    //while (1) {
    //    if (klc.keycheck(eag_Top)) {
    //        printf("a");
    //    }
    //    else if (klc.keycheck(eag_Bottom)) {
    //        printf("b");
    //    }
    //    else if (klc.keycheck(eag_Left)) {
    //        printf("c");
    //    }
    //    else if (klc.keycheck(eag_Right)) {
    //        printf("d");
    //    }
    //}

	GameLoop* game_loop = new GameLoop();
	game_loop->setFPS(12);
	game_loop->BuildScreen(160, 100, 8, 8);

	Sound my_sound = Sound();
	my_sound.playSound("hello.wav");

	vector<Object*> objects;
	game_loop->start( objects);

}