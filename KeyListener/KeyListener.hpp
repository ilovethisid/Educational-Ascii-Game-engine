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
	bool flag[EAG_VKEY_SIZE] = { false };//A~Z 0~9 �»���� (ȭ��ǥ) shift ctrl alt enter 
	bool keydownflag[EAG_VKEY_SIZE] = { false };
	bool doubleclickflag[EAG_VKEY_SIZE] = { false };
	bool klf = 1;//���α׷� �����
	bool Rf = 0;//�����ϴ� ���� �����带 ����
public:
	//public ����
	clock_t keydown_t[EAG_VKEY_SIZE] = { NULL };//���� Ű�ٿ�� ���� Ŭ���� �ð��� �����ϱ� ���� ����ϴ°�
	clock_t doubleclick_t[EAG_VKEY_SIZE] = { NULL };
	bool doubleclick_c[EAG_VKEY_SIZE] = { false };//���� Ŭ���� �ν��Ҷ� ���� ��Ȳ�� ������������ �ƴ����� Ȯ���ϴ� �뵵
	//Ű�Է��Լ�
	void keydowninput(int key);
	bool keydowncheck(int key);
	void doubleclickinput(int key);
	bool doubleclickcheck(int key);
	bool keycheck(int key);
	void keyinput(int key);
	//�׿����Լ�
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
