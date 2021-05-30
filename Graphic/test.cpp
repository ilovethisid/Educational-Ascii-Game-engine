#include <iostream>

#include "GraphicEngine.h"
#include "../game_loop.h"

using namespace std;
extern KeyListener klc;

int main(void) {


	GameLoop* game_loop = new GameLoop();
	game_loop->setFPS(12);
	game_loop->BuildScreen(50, 40, 20, 20);

	Sound my_sound = Sound();
	my_sound.playSound("hello.wav");

	vector<Object*> objects;
	game_loop->start( objects);

}