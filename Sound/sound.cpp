#include "sound.h"

Sound::Sound()
{
    
}

void Sound::playSound(std::string file)
{
    const char* c = file.c_str();
    wchar_t wstr[100] = {'\0', };
    CharToWChar(c, wstr);
    PlaySound(wstr, NULL, SND_FILENAME | SND_ASYNC); //일반 재생
}

// char to LPCWSTR
void Sound::CharToWChar(const char* pstrSrc, wchar_t pwstrDest[])
{
    int nLen = (int)strlen(pstrSrc) + 1;
    mbstowcs(pwstrDest, pstrSrc, nLen);
}