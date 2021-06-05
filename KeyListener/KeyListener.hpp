#pragma once
#include <thread>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include < Winuser.h>
#include <time.h>
#include "KeyMacro.hpp"

class KeyListener
{
private:
	bool flag[EAG_VKEY_SIZE] = { false };//A~Z 0~9 좌상우하 (화살표) shift ctrl alt enter 
	bool keydownflag[EAG_VKEY_SIZE] = { false };
	bool doubleclickflag[EAG_VKEY_SIZE] = { false };
	bool klf = 1;//프로그램 종료시
	bool Rf = 0;//리셋하는 동안 스레드를 멈춤
public:
	//public 변수
	clock_t keydown_t[EAG_VKEY_SIZE] = { NULL };//각각 키다운과 더블 클릭의 시간을 측정하기 위해 기록하는것
	clock_t doubleclick_t[EAG_VKEY_SIZE] = { NULL };
	bool doubleclick_c[EAG_VKEY_SIZE] = { false };//더블 클릭을 인식할때 직전 상황이 눌린상태인지 아닌지를 확인하는 용도
	//키입력함수
	void keydowninput(int key);
	bool keydowncheck(int key);
	void doubleclickinput(int key);
	bool doubleclickcheck(int key);
	bool keycheck(int key);
	void keyinput(int key);
	//그외의함수
	void reset();
	bool ReturnF();
	bool ReturnRf();
	int eagKeyToVK(int key);
	void exit();
};

class gameloop_t
{
private:
	std::thread* temp;
public:
	~gameloop_t(){
		delete temp;
	}
	void start();
	void end();
};
