#pragma once
#include <thread>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include < Winuser.h>
#include <time.h>
#define size 45//Ȯ���� ��ü Ű�� ����

class KeyListener
{
private:
	bool flag[size] = { false };//A~Z 0~9 �»���� (ȭ��ǥ) shift ctrl alt enter 
	bool keydownflag[size] = { false };
	bool doubleclickflag[size] = { false };
	bool klf = 1;//���α׷� �����
public:
	//public ����
	clock_t keydown_t[size] = { NULL };//���� Ű�ٿ�� ���� Ŭ���� �ð��� �����ϱ� ���� ����ϴ°�
	clock_t doubleclick_t[size] = { NULL };
	bool doubleclick_c[size] = { false };//���� Ŭ���� �ν��Ҷ� ���� ��Ȳ�� ������������ �ƴ����� Ȯ���ϴ� �뵵
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
	void exit();
};
