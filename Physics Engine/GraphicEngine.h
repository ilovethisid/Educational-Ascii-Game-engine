#pragma once
#ifndef UNICODE
#endif
#include <iostream>
#include  <windows.h>

enum COLOUR
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

typedef struct MATRIX {
	int maxRow;
	int maxColumn;
	short* cmatrix;
}MATRIX;


class Console{

protected:
	int screen_width;//콘솔 너비
	int screen_height;//콘솔 높이
	HANDLE m_hConsole;
	SMALL_RECT m_rectWindow;
	CHAR_INFO* bufScreen; //화면 저장
	CHAR_INFO* tmp_bufScreen;// 임시저장

public:
	Console(); //생성자 함수
	int make_console(int width, int height, int fontw, int fonth);
	void draw(int x, int y, short c = 0x2588, short col = 0x000F); //c= 채우는 문자 col= 색상
	void draw_circle(int x, int y, int r, short c = 0x2588, short col = 0x000F);
	void draw_line(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F);// 선그리기
	void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, short c = 0x2588, short col = 0x000F);// 삼각형 그리기

	void draw_square(int x, int y, int width, int height, short c = 0x2588, short col = 0x000F);//사각형 그리기
	void draw_matrix(int x, int y, MATRIX matrix, short col = 0x000F); // 배열 그리기

	void tmp_draw(int x, int y, short c = 0x2588, short col = 0x000F);//임시로 그리기
	void tmp_draw_matrix(int x, int y, MATRIX matrix, short col = 0x000F); //임시로 그리기
	void clear_buf(); //bufScreen 초기화

	MATRIX* make_circle(int r, short c=0x2588);
	MATRIX* make_square(int width, int height, short c = 0x2588);
	void update(); //tmp_bufScreen 출력
	void set_tmpbufScreen();
};