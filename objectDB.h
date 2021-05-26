#include "Object.cpp"
#include "Matrix.cpp"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void objectsave(Object *list, int count)
{
	ofstream out("objectDB.csv");
	string out_line;
	out << "x,y,width,height\n";
	for (int i = 0; i < count; i++)
	{
		out << list[i].getX() << ',';
		out << list[i].getY() << ',';
		out << list[i].getImage().width << ',';
		out << list[i].getImage().height << ',';
		out << '\n';
		int w = list[i].getImage().width;
		int h = list[i].getImage().height;
		for (int j = 0; j < h; j++)
		{
			for (int k = 0; k < w-1; k++)
			{
				out << list[i].getImage().element[j][k] << ',';
			}
			out << list[i].getImage().element[j][w-1] << '\n';
		}
	}
	out.close();
}
void objectread(Object *list, int count)
{
	string in_line;
	ifstream in("objectDB.csv");
	Matrix temp;
	getline(in, in_line);//���� ù���� x y ...�̹Ƿ� ����
	for (int i = 0; i < count; i++)
	{
		getline(in, in_line,',');
		//x���� list�� i��° object�� //object�� ������ �̿��� ������� x,y�� �����ϴ� ���� �𸣰ھ��...
		getline(in, in_line, ',');
		//y���� ����
		getline(in, in_line, ',');
		temp.width = stoi(in_line);
		getline(in, in_line, '\n');
		temp.height = stoi(in_line);
		int w = temp.width;
		int h = temp.height;
		temp.element = new short* [h];
		for (int j = 0; j < h; j++)
		{
			temp.element[j] = new short[w];
			for (int k = 0; k < w - 1; k++)
			{
				getline(in, in_line, ',');
				temp.element[j][k] = stoi(in_line);
			}
			getline(in, in_line, '\n');
			temp.element[j][w-1] = stoi(in_line);

		}
		list[i].makeImage(temp);
	}
	in.close();
}