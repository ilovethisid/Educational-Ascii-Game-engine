#include "KeyListener.hpp"
#include "KeyMacro.hpp"
#define KDT 2000//Ű�ٿ� �ð�
#define DCT 300//���� Ŭ�� ���� �ð�
KeyListener klc;

bool KeyListener::keycheck(int key)
{
	if (flag[key])//Ű�Է��� �޾Ҵµ� �ѹ��� ���۵� ���� �ʴ� ���� �����ϱ� ����
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
void KeyListener::reset()//����� �ؽ�Ʈ�� �޴´ٴ��� ���� ���� �����̶���� ���� �Է��� �����ؾ��ϴ� ��Ȳ���� ���
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
		for (i = 0x25; i < 0x29; i++)//�»����//Ű�ٿ��̳� ����Ŭ���� ����Ҹ��� ȭ��ǥ�� ���ؼ��� �����ý��ϴ�. ���Ѵٸ� ���ڸ� �ٲ㼭 ��� �����ϰ� ������� ����Ҳ���� ���� �Լ��� ���� ���ȭ�ϰڽ��ϴ�
		{
			if (GetAsyncKeyState(i))
			{
				clock_t temp = clock();
				klc.keyinput(i - 0x25 + 36);
				if (klc.keydown_t[i] != NULL)//Ű�ٿ�
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
				if (klc.doubleclick_t[i] != NULL)//���� Ŭ��
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
				klc.keydown_t[i] = NULL;//�Է��� ������ Ű�ٿ� �ð� ����
				if (klc.doubleclick_c[i])//����Ŭ��
				{
					klc.doubleclick_t[i] = clock();
				}
				klc.doubleclick_c[i] = false;
			}
		}
		if (GetAsyncKeyState(VK_SPACE))//�����̽���
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
