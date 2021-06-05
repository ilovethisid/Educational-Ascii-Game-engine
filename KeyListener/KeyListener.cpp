#include "KeyListener.hpp"
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
	Rf = 1;
	Sleep(500);
	for (int i = 0; i < EAG_VKEY_SIZE; i++)
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
int KeyListener::eagKeyToVK(int key)
{
	if (key >= EAG_VKEY_A && key <= EAG_VKEY_Z)
		key += 0x41;
	else if (key >= EAG_VKEY_0 && key <= EAG_VKEY_9)
		key += (0x30 - EAG_VKEY_0);
	else if (key == EAG_VKEY_SHIFT)
		key = VK_LSHIFT;
	else if (key == EAG_VKEY_CTRL)
		key = VK_LCONTROL;
	else if (key == EAG_VKEY_ALT)
		key = VK_LMENU;
	else if (key == EAG_VKEY_RETURN)
		key = VK_RETURN;
	else if (key >= EAG_VKEY_LEFT && key <= EAG_VKEY_DOWN)
		key += (VK_LEFT - EAG_VKEY_LEFT);
	else if (key == EAG_VKEY_SPACE)
		key = VK_SPACE;
	return key;
}
bool KeyListener::ReturnRf()
{
	if (Rf)
	{
		Rf = 0;
		return true;
	}
	return false;
}
void KeyListenerThread()
{
	int i;
	while (klc.ReturnF())
	{
		if (klc.ReturnRf())
		{
			Sleep(1000);
		}
		for (i = 0x41; i < 0x5B; i++)  // A~Z
		{
			if (GetAsyncKeyState(i))
			{
				klc.keyinput(i - 0x41);
			}
		}
		for (i = 0x30; i < 0x3A; i++)  // 0~9
		{
			if (GetAsyncKeyState(i))
			{
				klc.keyinput(i - 0x30 + EAG_VKEY_0);
			}
		}
		if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))  // SHIFT
		{
			klc.keyinput(EAG_VKEY_SHIFT);
		}
		if (GetAsyncKeyState(VK_LCONTROL) || GetAsyncKeyState(VK_RCONTROL))  // CTRL
		{
			klc.keyinput(EAG_VKEY_CTRL);
		}
		if (GetAsyncKeyState(VK_LMENU) || GetAsyncKeyState(VK_RMENU))  // ALT
		{
			klc.keyinput(EAG_VKEY_ALT);
		}
		if (GetAsyncKeyState(VK_RETURN))  // ENTER
		{
			klc.keyinput(EAG_VKEY_RETURN);
		}
		for (i = VK_LEFT; i < VK_SELECT; i++)//�»����//Ű�ٿ��̳� ����Ŭ���� ����Ҹ��� ȭ��ǥ�� ���ؼ��� �����ý��ϴ�. ���Ѵٸ� ���ڸ� �ٲ㼭 ��� �����ϰ� ������� ����Ҳ���� ���� �Լ��� ���� ���ȭ�ϰڽ��ϴ�
		{
			if (GetAsyncKeyState(i))
			{
				clock_t temp = clock();
				klc.keyinput(i - VK_LEFT + EAG_VKEY_LEFT);
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
			klc.keyinput(EAG_VKEY_SPACE);
		}
		if (GetAsyncKeyState(VK_ESCAPE))//�����̽���
		{
			klc.keyinput(EAG_VKEY_ESC);
		}

	}

}
void gameloop_t::start()
{
	temp = new std::thread(KeyListenerThread);
}
void gameloop_t::end()
{
	temp->join();
	delete temp;
}