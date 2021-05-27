#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <Windows.h>
#include <string>
#pragma comment(lib,"winmm.lib")


class Sound {

private:
    void CharToWChar(const char* pstrSrc, wchar_t pwstrDest[]);

public:
    Sound();
    void playSound(std::string file);
};