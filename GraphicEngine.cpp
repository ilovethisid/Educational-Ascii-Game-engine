#include  "GraphicEngine.h"
#include <algorithm>


Console::Console() {
	screen_width = 160;
	screen_height = 100;
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

int Console::make_console(int width, int height, int fontw, int fonth) {
	screen_width = width;
	screen_height = height;
	//screen buffer의 size 정함
	COORD coord = { (short)screen_width,(short)screen_height };
	if (!SetConsoleScreenBufferSize(m_hConsole, coord)) printf("ERROR1");
	if (!SetConsoleActiveScreenBuffer(m_hConsole)) printf("ERROR2");

	//font size를 콘솔에 assign
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontw;
	cfi.dwFontSize.Y = fonth;
	cfi.FontFamily = FF_DONTCARE;//폰트
	cfi.FontWeight = FW_NORMAL;//굵기
	wcscpy_s(cfi.FaceName, L"Consolas");//폰트

	if (!SetCurrentConsoleFontEx(m_hConsole, false, &cfi)) printf("ERROR3");

	// Get screen buffer info and check the maximum allowed window size. Return
	// error if exceeded, so user knows their dimensions/fontsize are too large
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(m_hConsole, &csbi)) printf("ERROR4");
	if (screen_height > csbi.dwMaximumWindowSize.Y) printf("ERROR5");//screen/font height too big
	if (screen_width > csbi.dwMaximumWindowSize.X) printf("ERROR6"); //screen/font width too big 

	//콘솔창 사이즈 조절
	m_rectWindow = { 0,0,(short)screen_width - 1,(short)screen_height - 1 };
	SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow);

	//스크린버퍼에 메모리 할당
	bufScreen = new CHAR_INFO[screen_width * screen_height];
	memset(bufScreen, 0, sizeof(CHAR_INFO) * screen_width * screen_height);
	//임시 스크린 버퍼에 메모리 할당
	tmp_bufScreen = new CHAR_INFO[screen_width * screen_height];
	memset(bufScreen, 0, sizeof(CHAR_INFO) * screen_width * screen_height);
	return 1;
}

void Console::draw(int x, int y, short c, short col ) {
	if (x >= 0 && x < screen_width && y >= 0 && y < screen_height)
	{
		bufScreen[y * screen_width + x].Char.UnicodeChar = c;
		bufScreen[y * screen_width + x].Attributes = col;
	}
}

void Console::tmp_draw(int x, int y, short c, short col) {
	if (x >= 0 && x < screen_width && y >= 0 && y < screen_height)
	{
		tmp_bufScreen[y * screen_width + x].Char.UnicodeChar = c;
		tmp_bufScreen[y * screen_width + x].Attributes = col;
	}
}

void Console::draw_circle(int rx, int ry, int r, short c, short col) {
	int x = 0;
	int y = r;
	while (y >= x) {
		draw(rx - x, ry - y, c, col);
		draw(rx - y, ry - x, c, col);
		draw(rx + y, ry - x, c, col);
		draw(rx + x, ry - y, c, col);
		draw(rx - x, ry + y, c, col);
		draw(rx - y, ry + x, c, col);
		draw(rx + y, ry + x, c, col);
		draw(rx + x, ry + y, c, col);
		x++;
		y=(int)(std::pow(r * r - x * x, 1 / 2.)+0.5);
	}
}

void Console::draw_square(int x, int y, int width, int height, short c, short col) {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			draw(x + i, y + j, c, col);
}

void Console::draw_line(int x1, int y1, int x2, int y2, short c, short col) {

	int addx = ((x2 - x1) > 0 ? 1 : -1);
	int addy = ((y2 - y1) > 0 ? 1 : -1);

	if (x1 == x2) {
		for (int i = y1; i != y2+addy; i += addy)
			draw(x1, i, c, col);
		return;
	}

	int j = y1;
	float slope = float(y2 - y1) / (x2 - x1);

	if (y1 <= y2) {
		for (int i = x1; i != x2; i = i + addx) {
			draw(i, j, c, col);
			for (j; j <= (slope * (0.5 * addx + i - x1) + y1); j += addy)
				draw(i, j, c, col);
		}
		for (j; j <=  y2 ; j += addy)
			draw(x2, j);
	}

	if (y1 > y2) {
		for (int i = x1; i != x2; i = i + addx) {
			draw(i, j, c, col);
			for (j; j >= (slope * (0.5 * addx + i - x1) + y1); j += addy)
				draw(i, j, c, col);
		}
		for (j; j >= y2 ; j += addy)
			draw(x2, j);
	}

}

void Console::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, short c, short col) {
	draw_line(x1, y1, x2, y2, c, col);
	draw_line(x2, y2, x3, y3, c, col);
	draw_line(x3, y3, x1, y1, c, col);
}

void Console::draw_Object(Object obj, short col) {
	Matrix tmp = obj.getImage();
	for (int i = 0; i < tmp.height; i++)
		for (int j = 0; j < tmp.width; j++)
			if (tmp.element[i][j]) draw(obj.getX() + i, obj.getY() + j, tmp.element[i][j], col);
}// 배열 그리기

void Console::tmp_draw_Object(Object obj, short col) {
	Matrix tmp = obj.getImage();
	for (int i = 0; i < tmp.height; i++)
		for (int j = 0; j < tmp.width; j++)
			if (tmp.element[i][j]) tmp_draw(obj.getX() + i, obj.getY() + j, tmp.element[i][j], col);
}// 배열 그리기

void Console::clear_buf() {
	memset(bufScreen, 0, sizeof(CHAR_INFO) * screen_width * screen_height);
}//bufScreen 초기화

Matrix Console::make_circle(int r, short c) {
	Matrix image =Matrix(2*r+1,2*r+1);
	int x = 0;
	int y = r;
	while (y >= x) {
		image.element[r - y][r - x] = c;
		image.element[r - x][r - y] = c;
		image.element[r - x][r + y] = c;
		image.element[r - y][r + x] = c;
		image.element[r + y][r - x] = c;
		image.element[r +x][r - y] = c;
		image.element[r +y][r +x] = c;
		image.element[r +x][r +y] = c;
		x++;
		y = (int)(std::pow(r * r - x * x, 1 / 2.) + 0.5);
	}
	return image;
}


Matrix Console::make_square(int width, int height, short c){
	Matrix image = Matrix(width, height);
	for(int i=0; i<height;i++)
		std::fill_n(image.element[i], width, c);
	return image;
}

void Console::set_tmpbufScreen() {//tmpbufScreen
	memcpy(tmp_bufScreen, bufScreen, screen_width * screen_height*sizeof(CHAR_INFO));
}

void Console::update() { //출력하는 함수
		WriteConsoleOutput(m_hConsole, tmp_bufScreen, { (short)screen_width, (short)screen_height }, { 0,0 }, &m_rectWindow);
	}