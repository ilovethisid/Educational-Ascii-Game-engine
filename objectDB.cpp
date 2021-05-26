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
	getline(in, in_line);//가장 첫줄은 x y ...이므로 제외
	for (int i = 0; i < count; i++)
	{
		getline(in, in_line,',');
		//x값을 list의 i번째 object에 //object에 생성자 이외의 방법으로 x,y를 수정하는 법을 모르겠어요...
		getline(in, in_line, ',');
		//y값을 저장
		getline(in, in_line, ',');
		temp.width = atoi(in_line.c_str());
		getline(in, in_line, ',');
		temp.height = atoi(in_line.c_str());
		getline(in, in_line, '\n');
		//temp.element = atoi(in_line.c_str());
		//short**인걸로 봐서 주소인거 같은데 주소를 저장해뒀다가 다시 가져와도 그 주소에 의미가 없을꺼 같습니다
		list[i].makeImage(temp);
	}
	in.close();
}