#include  "GraphicEngine.h"
#include <algorithm>


Console::Console() {
	screen_width = 160;
	screen_height = 100;
	console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

int Console::makeConsole(int width, int height, int fontw, int fonth) {
	screen_width = width;
	screen_height = height;
	//screen buffer의 size 정함
	COORD coord = { (short)screen_width,(short)screen_height };
	if (!SetConsoleScreenBufferSize(console_handle, coord)) printf("ERROR1");
	if (!SetConsoleActiveScreenBuffer(console_handle)) printf("ERROR2");

	//font size를 콘솔에 assign
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontw;
	cfi.dwFontSize.Y = fonth;
	cfi.FontFamily = FF_DONTCARE;//폰트
	cfi.FontWeight = FW_NORMAL;//굵기
	wcscpy_s(cfi.FaceName, L"Consolas");//폰트

	if (!SetCurrentConsoleFontEx(console_handle, false, &cfi)) printf("ERROR3");

	// Get screen buffer info and check the maximum allowed window size. Return
	// error if exceeded, so user knows their dimensions/fontsize are too large
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(console_handle, &csbi)) printf("ERROR4");
	if (screen_height > csbi.dwMaximumWindowSize.Y) printf("ERROR5");//screen/font height too big
	if (screen_width > csbi.dwMaximumWindowSize.X) printf("ERROR6"); //screen/font width too big 

	//콘솔창 사이즈 조절
	window_rect = { 0,0,(short)screen_width - 1,(short)screen_height - 1 };
	SetConsoleWindowInfo(console_handle, TRUE, &window_rect);

	//스크린버퍼에 메모리 할당
	screen_buffer = new CHAR_INFO[screen_width * screen_height];
	memset(screen_buffer, 0, sizeof(CHAR_INFO) * screen_width * screen_height);
	//임시 스크린 버퍼에 메모리 할당
	tmp_screen_buffer = new CHAR_INFO[screen_width * screen_height];
	memset(screen_buffer, 0, sizeof(CHAR_INFO) * screen_width * screen_height);
	return 1;
}

void Console::draw(int x, int y, short c, short col ) {
	if (x >= 0 && x < screen_width && y >= 0 && y < screen_height)
	{
		screen_buffer[y * screen_width + x].Char.UnicodeChar = c;
		screen_buffer[y * screen_width + x].Attributes = col;
	}
}

void Console::drawTmp(int x, int y, short c, short col) {
	if (x >= 0 && x < screen_width && y >= 0 && y < screen_height)
	{
		tmp_screen_buffer[y * screen_width + x].Char.UnicodeChar = c;
		tmp_screen_buffer[y * screen_width + x].Attributes = col;
	}
}

void Console::drawCircle(int rx, int ry, int r, short c, short col) {
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

void Console::drawSquare(int x, int y, int width, int height, short c, short col) {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			draw(x + i, y + j, c, col);
}
void Console::drawLineInMatrix(short*** pnt,int x1, int y1, int x2, int y2, short c) {
	short** element = *pnt;
	int addx = ((x2 - x1) > 0 ? 1 : -1);
	int addy = ((y2 - y1) > 0 ? 1 : -1);

	if (x1 == x2) {
		for (int i = y1; i != y2 + addy; i += addy)
			element[i][x1] = c;
		return;
	}

	int j = y1;
	float slope = float(y2 - y1) / (x2 - x1);

	if (y1 <= y2) {
		for (int i = x1; i != x2; i = i + addx) {
			element[j][i] = c;
			for (j; j <= (slope * (0.5 * addx + i - x1) + y1); j += addy)
				element[j][i] = c;
		}
		for (j; j <= y2; j += addy)
			element[j][x2] = c;
	}

	if (y1 > y2) {
		for (int i = x1; i != x2; i = i + addx) {
			element[j][i] = c;
			for (j; j >= (slope * (0.5 * addx + i - x1) + y1); j += addy)
				element[j][i] = c;
		}
		for (j; j >= y2; j += addy)
			element[j][x2] = c;
	}
}
void Console::drawLine(int x1, int y1, int x2, int y2, short c, short col) {

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

void Console::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c, short col) {
	drawLine(x1, y1, x2, y2, c, col);
	drawLine(x2, y2, x3, y3, c, col);
	drawLine(x3, y3, x1, y1, c, col);
}

void Console::drawObject(Object obj, short col) {
	Matrix tmp = obj.getImage();
	for (int i = 0; i < tmp.height; i++)
		for (int j = 0; j < tmp.width; j++)
			if (tmp.element[i][j]) draw(obj.getX() + i, obj.getY() + j, tmp.element[i][j], col);
}// 배열 그리기

void Console::drawTmpObject(Object obj, short col) {
	Matrix tmp = obj.getImage();
	for (int i = 0; i < tmp.height; i++)
		for (int j = 0; j < tmp.width; j++)
			if (tmp.element[i][j]) drawTmp(obj.getX() + i, obj.getY() + j, tmp.element[i][j], col);
}// 배열 그리기

void Console::clearTmpBufScreen() {
	memset(screen_buffer, 0, sizeof(CHAR_INFO) * screen_width * screen_height);
}//bufScreen 초기화

Matrix Console::makeCircle(int r, short c) {
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

Matrix Console::makeTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c, short col) {

	Matrix image = Matrix(max(max(x1, x2), x3)+1, max(max(y1, y2), y3)+1);
	drawLineInMatrix(&image.element, x1, y1, x2, y2, c);
	drawLineInMatrix(&image.element, x2, y2, x3, y3, c);
	drawLineInMatrix(&image.element, x3, y3, x1, y1, c);
	return image;
}

Matrix Console::makeSquare(int width, int height, short c){
	Matrix image = Matrix(width, height);
	for(int i=0; i<height;i++)
		std::fill_n(image.element[i], width, c);
	return image;
}

void Console::setTmpBufScreen() {//tmpbufScreen
	memcpy(tmp_screen_buffer, screen_buffer, screen_width * screen_height*sizeof(CHAR_INFO));
}

void Console::update() { //출력하는 함수
		WriteConsoleOutput(console_handle, tmp_screen_buffer, { (short)screen_width, (short)screen_height }, { 0,0 }, &window_rect);
	}