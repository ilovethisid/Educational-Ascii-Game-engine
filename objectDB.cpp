#include "Object.cpp"
#include "Matrix.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

void objectsave(Object *list, int count)
{
	ofstream out("objectDB.csv");
	string out_line;
	out << "x,y,width,height,element\n";
	for (int i = 0; i < count; i++)
	{
		out << list[i].getX() << ',';
		out << list[i].getY() << ',';
		out << list[i].getImage().width << ',';
		out << list[i].getImage().height << ',';
		out << list[i].getImage().element << '\n';
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
		temp.width = atoi(in_line.c_str());
		getline(in, in_line, ',');
		temp.height = atoi(in_line.c_str());
		getline(in, in_line, '\n');
		//temp.element = atoi(in_line.c_str());
		//short**�ΰɷ� ���� �ּ��ΰ� ������ �ּҸ� �����ص״ٰ� �ٽ� �����͵� �� �ּҿ� �ǹ̰� ������ �����ϴ�
		list[i].makeImage(temp);
	}
	in.close();
}