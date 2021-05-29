#include <iostream>

#include "GraphicEngine.h"
#include "../game_loop.h"

using namespace std;

int main(void) {

	Console demo;
	demo.makeConsole(160, 100, 8, 8);

	GameLoop* game_loop = new GameLoop();
	game_loop->setFPS(12);
	game_loop->BuildScreen(160, 100, 8, 8);

	Sound my_sound = Sound();
	my_sound.playSound("hello.wav");

	vector<Object*> objects;
	game_loop->start(demo, objects);

}