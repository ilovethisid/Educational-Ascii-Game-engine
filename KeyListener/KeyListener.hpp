#pragma once
#include <thread>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include < Winuser.h>
#include <time.h>
#define SIZE 45//Ȯ���� ��ü Ű�� ����

class KeyListener
{
private:
	bool flag[SIZE] = { false };//A~Z 0~9 �»���� (ȭ��ǥ) shift ctrl alt enter 
	bool keydownflag[SIZE] = { false };
	bool doubleclickflag[SIZE] = { false };
	bool klf = 1;//���α׷� �����
public:
	//public ����
	clock_t keydown_t[SIZE] = { NULL };//���� Ű�ٿ�� ���� Ŭ���� �ð��� �����ϱ� ���� ����ϴ°�
	clock_t doubleclick_t[SIZE] = { NULL };
	bool doubleclick_c[SIZE] = { false };//���� Ŭ���� �ν��Ҷ� ���� ��Ȳ�� ������������ �ƴ����� Ȯ���ϴ� �뵵
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
