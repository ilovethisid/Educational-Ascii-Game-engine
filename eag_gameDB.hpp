//case1 시작 시점과 종료 시점에 파일 갯수나 크기가 변할 수 있는 게임일 경우
//시작 시점에서 gameDB생성 roadinfo로 저장된 파일 정보를 가져옴 그후 roadfile로 파일명으로 정보를 가져옴 이후 소멸자로 제거
//종료 시점 새로 생성하고 savefile로 저장할 정보들을 저장하고 saveinfo로 저장한 파일들의 정보들을 저장
//case2 시작 시점과 종료 시점에 파일 갯수 크기의 변화 없이 단순한 값만 변할 경우
//시작 시점에서 생성한 gameDB를 끝날때도 그대로 사용
//roadinfo로 파일 정보를 로드하고 roadfile로 가져옴
//종료 시점에서 기존의 gameDB에서 savefile(case2)를 이용해서 저장
//saveinfo는 불필요 어쳐피 동일하고 안 사라짐
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#define INT_T 1
#define STRING_T 0
using namespace std;
void saveint1d(int* input, int num, string name)
{
	ofstream out(name);
	out << input[0];
	for (int i = 1; i < num; i++)
	{
		out << ',' << input[i];
	}
	out << '\n';
	out.close();
}
void roadint1d(int** target, int num, string name)
{
	*target = new int[num];
	ifstream in(name);
	string in_line;
	for (int i = 0; i < num-1; i++)
	{
		getline(in, in_line, ',');
		(*target)[i]=stoi(in_line);
	}
	getline(in, in_line, '\n');
	(*target)[num-1] = stoi(in_line);
	in.close();
}
void saveint2d(int** input, int h,int w, string name)
{
	ofstream out(name);
	for (int i = 0; i < h; i++)
	{
		out << input[i][0];
		for (int j = 1; j < w; j++)
		{
			out << ',' << input[i][j];
		}
		out << '\n';
	}
	out.close();
}
void roadint2d(int*** target, int h, int w, string name)
{
	*target = new int*[h];
	for (int i = 0; i < h; i++)
	{
		(*target)[i] = new int[w];
	}
	ifstream in(name);
	string in_line;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w - 1; j++)
		{
			getline(in, in_line, ',');
			(*target)[i][j] = stoi(in_line);
		}
		getline(in, in_line, '\n');
		(*target)[i][w-1] = stoi(in_line);
	}
	in.close();
}
void saveString1d(string* input, int num, string name)
{
	ofstream out(name);
	out << input[0];
	for (int i = 1; i < num; i++)
	{
		out << ',' << input[i];
	}
	out << '\n';
	out.close();
}
void roadString1d(string** target, int num, string name)
{
	*target = new string[num];
	ifstream in(name);
	string in_line;
	for (int i = 0; i < num - 1; i++)
	{
		getline(in, in_line, ',');
		(*target)[i] = in_line;
	}
	getline(in, in_line, '\n');
	(*target)[num - 1] = in_line;
	in.close();
}
void saveString2d(string** input, int h, int w, string name)
{
	ofstream out(name);
	for (int i = 0; i < h; i++)
	{
		out << input[i][0];
		for (int j = 1; j < w; j++)
		{
			out << ',' << input[i][j];
		}
		out << '\n';
	}
	out.close();
}
void roadString2d (string*** target, int h, int w, string name)
{
	*target = new string*[h];
	for (int i = 0; i < h; i++)
	{
		(*target)[i] = new string[w];
	}
	ifstream in(name);
	string in_line;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w - 1; j++)
		{
			getline(in, in_line, ',');
			(*target)[i][j] = in_line;
		}
		getline(in, in_line, '\n');
		(*target)[i][w - 1] = in_line;
	}
	in.close();
}
class fileinfo
{
public:
	string filename;
	int filetype;//0 string 1 int
	int filesize[2];
	fileinfo()
	{
		filename = "defult.csv";
		filetype = INT_T;
		filesize[0] = 0;
		filesize[1] = 0;
	}
	fileinfo(string _filename, int _filetpye, int _filesizeh, int _filesizew)
	{
		filename = _filename;
		filetype = _filetpye;
		filesize[0] = _filesizeh;
		filesize[1] = _filesizew;
	}
};
class gameDB
{
private:
	fileinfo *file;
	int filenum;
public:
	gameDB()
	{
		file = NULL;
		filenum = 0;
	}
	~gameDB()
	{
		delete[] file;
	}
	void savefile(void* input, int _filetpye, int _filesizeh, int _filesizew,string _filename)//case1
	{
		if (_filetpye = INT_T)
		{
			if (_filesizew == 0)
			{
				saveint1d((int*)input, _filesizeh,_filename);
			}
			else
			{
				saveint2d((int**)input, _filesizeh, _filesizew, _filename);
			}
		}
		else if (_filetpye = STRING_T)
		{
			if (_filesizew == 0)
			{
				saveString1d((string*)input, _filesizeh, _filename);
			}
			else
			{
				saveString2d((string**)input, _filesizeh, _filesizew, _filename);
			}
		}
		else { return; }//error
		filenum++;
		fileinfo *new_file = new fileinfo[filenum];
		for (int i = 0; i < filenum - 1; i++)
		{
			new_file[i] = file[i];
		}
		new_file[filenum - 1].filename = _filename;
		new_file[filenum - 1].filesize[0] = _filesizeh;
		new_file[filenum - 1].filesize[1] = _filesizew;
		new_file[filenum - 1].filetype = _filetpye;
	}
	void savefile(void* input, string _filename)//case2
	{
		int count = 0;
		void **result = new void*;
		while (file[count].filename != _filename)
		{
			if (count < filenum - 1)
			{
				count++;
			}
			else
			{
				return;//error
			}
		}
		int _filetype = file[count].filetype;
		int _filesizew = file[count].filesize[0];
		int _filesizeh = file[count].filesize[1];
		if (_filetype = INT_T)
		{
			if (_filesizew == 0)
			{
				saveint1d((int*)input, _filesizeh, _filename);
			}
			else
			{
				saveint2d((int**)input, _filesizeh, _filesizew, _filename);
			}
		}
		else if (_filetype = STRING_T)
		{
			if (_filesizew == 0)
			{
				saveString1d((string*)input, _filesizeh, _filename);
			}
			else
			{
				saveString2d((string**)input, _filesizeh, _filesizew, _filename);
			}
		}
		else { return; }//error
	}
	void saveinfo()
	{
		ofstream out("saveinfo.csv");
		out << filenum << '\n';
		for (int i = 0; i < filenum; i++)
		{
			out << file[i].filename << ',';
			out << file[i].filetype << ',';
			out << file[i].filesize[0] << ',';
			out << file[i].filesize[1] << '\n';
		}
		out.close();
	}
	void roadinfo()
	{
		ifstream in("saveinfo.csv");
		string in_line;
		getline(in, in_line, '\n');
		filenum = stoi(in_line);
		file = new fileinfo[filenum];
		for (int i = 0; i < filenum; i++)
		{
			getline(in, in_line, ',');
			file[i].filename = in_line;
			getline(in, in_line, ',');
			file[i].filetype = stoi(in_line);
			getline(in, in_line, ',');
			file[i].filesize[0] = stoi(in_line);
			getline(in, in_line, ',');
			file[i].filesize[1] = stoi(in_line);
		}
	}
	void* roadfile(string _filename)
	{
		int count = 0;
		void **result = new void*;
		while (file[count].filename != _filename)
		{
			if (count < filenum-1)
			{
				count++;
			}
			else
			{
				return NULL;//error
			}
		}
		if (file[count].filetype == INT_T)
		{
			if (file[count].filesize[1] == 0)//int1d
			{
				roadint1d((int**)(&result), file[count].filesize[0], _filename);
			}
			else //int2d
			{
				roadint2d((int***)(&result), file[count].filesize[0], file[count].filesize[1], _filename);
			}
		}
		else if (file[count].filetype == STRING_T)
		{
			if (file[count].filesize[1] == 0)//stirng1d
			{
				roadString1d((string**)(&result), file[count].filesize[0], _filename);
			}
			else //string2d
			{
				roadString2d((string***)(&result), file[count].filesize[0], file[count].filesize[1], _filename);
			}
		}
		return &result;
	}
};