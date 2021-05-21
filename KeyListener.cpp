#include "KeyListener.hpp"
#include "KeyMacro.hpp"
#define KDT 2000//키다운 시간
#define DCT 300//더블 클릭 여유 시간
KeyListener klc;

bool KeyListener::keycheck(int key)
{
	if (flag[key])//키입력을 받았는데 한번의 동작도 하지 않는 것을 방지하기 위함
	{
		flag[key] = 0;
		return 1;
	}
	else { return 0; }
}
void KeyListener::keyinput(int key)
{
	flag[key] = 1;
}
void KeyListener::reset()//사용자 텍스트를 받는다던가 게임 시작 시점이라던가 이전 입력을 무시해야하는 상황에서 사용
{
	for (int i = 0; i < 43; i++)
	{
		flag[i] = false;
		keydownflag[i] = false;
		doubleclickflag[i] = false;
	}
}
bool KeyListener::ReturnF()
{
	return klf;
}
void KeyListener::exit()
{
	klf = 0;
}
void KeyListener::keydowninput(int key)
{
	keydownflag[key] = true;
}
bool KeyListener::keydowncheck(int key)
{
	if (keydownflag[key])
	{
		keydownflag[key] = false;
		return true;
	}
	else { return false; }
}
void KeyListener::doubleclickinput(int key)
{
	doubleclickflag[key] = true;
}
bool KeyListener::doubleclickcheck(int key)
{
	if (doubleclickflag[key])
	{
		doubleclickflag[key] = false;
		return true;
	}
	return false;
}
void KeyListenerThread()
{
	int i;
	while (klc.ReturnF())
	{
		if (GetAsyncKeyState(0xA2) || GetAsyncKeyState(0xA3))
		{
		}
		for (i = 0x41; i < 0x5B; i++)//A~Z
		{
			if (GetAsyncKeyState(i))
			{
				klc.keyinput(i - 0x41);
			}
		}
		for (i = 0x30; i < 0x3A; i++)//0~9
		{
			if (GetAsyncKeyState(i))
			{
				klc.keyinput(i - 0x30 + 26);
			}
		}
		if (GetAsyncKeyState(0xA0) || GetAsyncKeyState(0xA1))//shift
		{
			klc.keyinput(40);
		}
		if (GetAsyncKeyState(0xA2) || GetAsyncKeyState(0xA3))//ctrl
		{
			klc.keyinput(41);
		}
		if (GetAsyncKeyState(0xA4) || GetAsyncKeyState(0xA5))//Alt
		{
			klc.keyinput(42);
		}
		if (GetAsyncKeyState(0x0D))//enter
		{
			klc.keyinput(43);
		}
		for (i = 0x25; i < 0x29; i++)//좌상우하//키다운이나 더블클릭을 사용할만한 화살표에 대해서만 만들어봤습니다. 원한다면 숫자를 바꿔서 사용 가능하고 어기저기 사용할꺼라면 차라리 함수를 만들어서 모듈화하겠습니다
		{
			if (GetAsyncKeyState(i))
			{
				clock_t temp = clock();
				klc.keyinput(i - 0x25 + 36);
				if (klc.keydown_t[i] != NULL)//키다운
				{
					if (temp - klc.keydown_t[i] >= KDT)
					{
						klc.keydowninput(i);
					}
				}
				else
				{
					klc.keydown_t[i] = temp;
				}
				if (klc.doubleclick_t[i] != NULL)//더블 클릭
				{
					if (!klc.doubleclick_c[i] && clock() - klc.doubleclick_t[i] < DCT)
					{
						klc.doubleclick_t[i];
					}
				}
				klc.doubleclick_c[i] = true;
			}
			else
			{
				clock_t temp = clock();
				klc.keydown_t[i] = NULL;//입력이 없으면 키다운 시간 리셋
				if (klc.doubleclick_c[i])//더블클릭
				{
					klc.doubleclick_t[i] = clock();
				}
				klc.doubleclick_c[i] = false;
			}
		}
		if (GetAsyncKeyState(VK_SPACE))//스페이스바
		{
			klc.keyinput(44);
		}

	}

}
class gameloop_t
{
private:
	std::thread* temp;
public:
	void start()
	{
		temp = new std::thread(KeyListenerThread);
	}
	void end()
	{
		temp->join();
	}
};
