#include  "GraphicEngine.h"
#include <algorithm>
using namespace std;

Console::Console() {
	screen_width = 160;
	screen_height = 100;
	console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	screen_buffer = NULL;
	tmp_screen_buffer = NULL;
}

int Console::makeConsole(int width, int height, int fontw, int fonth) {
	screen_width = width;
	screen_height = height;
	//screen buffer의 size 정함

	window_rect = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(console_handle , TRUE, &window_rect);

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

void Console::drawRect(int x, int y, int width, int height, short c, short col) {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			draw(x + i, y + j, c, col);
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

void Console::drawObject(Object& obj) {
	Matrix tmp = Matrix(obj.getImage());
	for (int i = 0; i < tmp.height; i++)
		for (int j = 0; j < tmp.width; j++)
			if (tmp.element[i][j]) draw(obj.getX() + j, obj.getY() + i, tmp.element[i][j], tmp.color[i*tmp.width+j]);
}// 배열 그리기

void Console::drawMatrix(int x, int y, Matrix& image) {

	for (int i = 0; i < image.height; i++)
		for (int j = 0; j < image.width; j++)
			if (image.element[i][j]) draw(x + j, y + i, image.element[i][j], image.color[i * image.width + j]);
}



void Console::drawTmpObject(Object& obj) {
	Matrix tmp = Matrix(obj.getImage());
	for (int i = 0; i < tmp.height; i++)
		for (int j = 0; j < tmp.width; j++)
			if (tmp.element[i][j]) drawTmp(obj.getX() + j, obj.getY() + i, tmp.element[i][j], tmp.color[i * tmp.width + j]);
}

void Console::drawTmpObjects(vector<Object*> objects)
{
	for (int i = 0; i < objects.size(); i++) {
		drawTmpObject(*objects[i]);
	}
}
// 배열 그리기

void Console::clearTmpBufScreen() {
	memset(screen_buffer, 0, sizeof(CHAR_INFO) * screen_width * screen_height);
}//bufScreen 초기화


wstringstream readFile(const char* filename) {
	wifstream wif(filename);
	wif.imbue(locale(std::locale::empty(), new codecvt_utf8<wchar_t>));
	wstringstream wss;
	wss << wif.rdbuf();
	wif.close();
	return wss;
}

Matrix makeFile2Matrix(const char* filename){
	wstringstream wss = readFile(filename);

	wstring temp;

	int width;
	getline(wss, temp, L',');
	width = stoi(temp);

	int height;
	getline(wss, temp, L',');
	height = stoi(temp);

	Matrix image = Matrix(width, height);

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {

			int fr, fg, fb, br, bg, bb;

			getline(wss, temp, L',');
			fr = stoi(temp);
			getline(wss, temp, L',');
			fg = stoi(temp);
			getline(wss, temp, L',');
			fb = stoi(temp);
			getline(wss, temp, L',');
			getline(wss, temp, L',');
			br = stoi(temp);
			getline(wss, temp, L',');
			bg = stoi(temp);
			getline(wss, temp, L',');
			bb = stoi(temp);
			getline(wss, temp, L',');
			getline(wss, temp, L',');

			unsigned char color = 0;
			if (fb>30) color += 1;
			if (fg>30) color += 2;
			if (fr>30) color += 4;
			if (bb>30) color += 16;
			if (bg>30) color += 32;
			if (br>30) color += 64;
			if ((fr+fg+fb)&&fr < 200 && fg < 200 && fb < 200) color += 8;
			if ((br + bg + bb) && br < 200 && bg < 200 && bb < 200) color += 128;
			unsigned short c = temp[0];
			if(c!= 78)image.element[i][j] = c;
			if (c == 78)image.element[i][j] = 0;
			
			image.color[i * width + j] = color;
		}
	}
	wss.str(L"");
	return image;
}


void Console::setTmpBufScreen() {//tmpbufScreen
	memcpy(tmp_screen_buffer, screen_buffer, screen_width * screen_height*sizeof(CHAR_INFO));
}

int Console::getScreenWidth()
{
	return screen_width;
}

int Console::getScreenHeight()
{
	return screen_height;
}

void Console::update() { //출력하는 함수
		WriteConsoleOutput(console_handle, tmp_screen_buffer, { (short)screen_width, (short)screen_height }, { 0,0 }, &window_rect);
	}

void Console::print(string str, int line, int start) {
	int j = start;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '\n') {
			j = 0;
			line++;
		}
		else
			draw(j++, line, str[i]);
	}
}


Matrix makeCircle(int r, short c, short col) {
	Matrix tmp = Matrix(2 * r + 1, 2 * r + 1);
	memset(tmp.color, (unsigned char)col, sizeof(unsigned char) * tmp.width * tmp.height);
	int x = 0;
	int y = r;
	while (y >= x) {
		tmp.element[r - y][r - x] = c;
		tmp.element[r - x][r - y] = c;
		tmp.element[r - x][r + y] = c;
		tmp.element[r - y][r + x] = c;
		tmp.element[r + y][r - x] = c;
		tmp.element[r + x][r - y] = c;
		tmp.element[r + y][r + x] = c;
		tmp.element[r + x][r + y] = c;
		x++;
		y = (int)(std::pow(r * r - x * x, 1 / 2.) + 0.5);
	}
	return tmp;
}

Matrix makeTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c, short col) {

	Matrix tmp = Matrix(max(max(x1, x2), x3) + 1, max(max(y1, y2), y3) + 1);
	memset(tmp.color, (unsigned char)col, sizeof(unsigned char) * tmp.width * tmp.height);
	drawLineInMatrix(&tmp.element, x1, y1, x2, y2, c);
	drawLineInMatrix(&tmp.element, x2, y2, x3, y3, c);
	drawLineInMatrix(&tmp.element, x3, y3, x1, y1, c);
	return tmp;
}

Matrix makeRect(int width, int height, short c, short col) {
	Matrix tmp = Matrix(width, height);
	memset(tmp.color, (unsigned char)col, sizeof(unsigned char) * tmp.width * tmp.height);
	for (int i = 0; i < height; i++)
		std::fill_n(tmp.element[i], width, c);
	return tmp;
}

Matrix makeBox(int width, int height, short thickness, short c, short col) {
	Matrix tmp = Matrix(width, height);
	memset(tmp.color, (unsigned char)col, sizeof(unsigned char) * tmp.width * tmp.height);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < thickness; j++)
		{
			tmp.element[i][j] = c;
			tmp.element[i][width - 1 - j] = c;
		}
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < thickness; j++)
		{
			tmp.element[j][i] = c;
			tmp.element[height - 1 - j][i] = c;
		}
	}

	return tmp;
}

void drawLineInMatrix(short*** pnt, int x1, int y1, int x2, int y2, short c) {
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