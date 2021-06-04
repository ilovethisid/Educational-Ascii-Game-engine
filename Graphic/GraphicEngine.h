#pragma once
#ifndef UNICODE
#endif
#include <iostream>

#include <sstream>
#include <fstream>
#include <codecvt>
#include <vector>

#include  <windows.h>
#include "../Physics/Object.h"

enum COLOR
{
	FG_BLACK = 0x0000,
	FG_DARK_BLUE = 0x0001,
	FG_DARK_GREEN = 0x0002,
	FG_DARK_CYAN = 0x0003,
	FG_DARK_RED = 0x0004,
	FG_DARK_MAGENTA = 0x0005,
	FG_DARK_YELLOW = 0x0006,
	FG_GREY = 0x0007, 
	FG_DARK_GREY = 0x0008,
	FG_BLUE = 0x0009,
	FG_GREEN = 0x000A,
	FG_CYAN = 0x000B,
	FG_RED = 0x000C,
	FG_MAGENTA = 0x000D,
	FG_YELLOW = 0x000E,
	FG_WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0,
};

enum PIXEL_TYPE
{
	PIXEL_SOLID = 0x2588,
	PIXEL_THREEQUARTERS = 0x2593,
	PIXEL_HALF = 0x2592,
	PIXEL_QUARTER = 0x2591,
};


class Console{

protected:
	int screen_width;//�ܼ� �ʺ�
	int screen_height;//�ܼ� ����
	HANDLE console_handle;
	SMALL_RECT window_rect;
	CHAR_INFO* screen_buffer; //ȭ�� ����
	CHAR_INFO* tmp_screen_buffer;// �ӽ�����
	char tmp;//RVO ��

public:
	Console(); //������ �Լ�
	//~Console() {
	//	delete screen_buffer;
	//	delete tmp_screen_buffer;
	//}
	int makeConsole(int width, int height, int fontw, int fonth);
	void draw(int x, int y, short c = PIXEL_SOLID, short col = FG_WHITE); //c= ä��� ���� col= ����
	void drawCircle(int x, int y, int r, short c = PIXEL_SOLID, short col = FG_WHITE);
	void drawLine(int x1, int y1, int x2, int y2, short c = PIXEL_SOLID, short col = FG_WHITE);// ���׸���
	void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c = PIXEL_SOLID, short col = FG_WHITE);// �ﰢ�� �׸���

	void drawRect(int x, int y, int width, int height, short c = PIXEL_SOLID, short col = 0x000F);//�簢�� �׸���
	void drawObject(Object& obj); // �迭 �׸���
	void drawMatrix(int x,int y,Matrix& image);

	void drawTmp(int x, int y, short c = PIXEL_SOLID, short col = FG_WHITE);//�ӽ÷� �׸���
	void drawTmpObject(Object& obj); //�ӽ÷� �׸���
	void drawTmpObjects(vector<Object*> objects ); //�ӽ÷� �׸���
	void clearTmpBufScreen(); //bufScreen �ʱ�ȭ

	Matrix makeCircle(int r, short c= PIXEL_SOLID, short col = FG_WHITE);
	Matrix makeRect(int width, int height, short c = PIXEL_SOLID, short col = FG_WHITE);
	Matrix makeBox(int width, int height, short c = PIXEL_SOLID, short col = FG_WHITE);
	Matrix makeTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c = PIXEL_SOLID, short col = FG_WHITE);//�ﰢ�� ����
	void drawLineInMatrix(short*** pnt, int x1, int y1, int x2, int y2, short c = PIXEL_SOLID);
	Matrix makeFile2Matrix(const char* filename);

	void print(string str, int line, int start); //���ڿ� ��¿��Լ�
	void update(); //tmp_bufScreen ���
	void setTmpBufScreen();
	int getScreenWidth();
	int getScreenHeight();
};

wstringstream readFile(const char* filename);