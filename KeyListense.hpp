#pragma once
#include <thread>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include < Winuser.h>
class KeyListener
{
private:
	bool flag[45] = { false };//A~Z 0~9 �»���� (ȭ��ǥ) shift ctrl alt enter 
	bool klf = 1;//���α׷� �����
public:
	bool keycheck(int key);
	void keyinput(int key);
	void reset();
	bool ReturnF();
	void exit();
};