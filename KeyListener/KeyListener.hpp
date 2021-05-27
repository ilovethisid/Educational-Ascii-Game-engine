#pragma once
#include <thread>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include < Winuser.h>
#include <time.h>
#define size 45//확인할 전체 키의 갯수

class KeyListener
{
private:
	bool flag[size] = { false };//A~Z 0~9 좌상우하 (화살표) shift ctrl alt enter 
	bool keydownflag[size] = { false };
	bool doubleclickflag[size] = { false };
	bool klf = 1;//프로그램 종료시
public:
	//public 변수
	clock_t keydown_t[size] = { NULL };//각각 키다운과 더블 클릭의 시간을 측정하기 위해 기록하는것
	clock_t doubleclick_t[size] = { NULL };
	bool doubleclick_c[size] = { false };//더블 클릭을 인식할때 직전 상황이 눌린상태인지 아닌지를 확인하는 용도
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
	void exit();
};
