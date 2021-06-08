
#define _CRT_SECURE_NO_WARNINGS
#define LASER "C:\\Users\\ilove\\source\\repos\\Educational-Ascii-Game-engine\\usrlib\\laser-gun.wav" // 효과음 경로 지정

#include <iostream>

#include "sound.h"

MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;
MCI_STATUS_PARMS   mciStatus; //파일의 상태


UINT wDeviceID = 0;

int dwID;

wchar_t* wchar(const char* pstrSrc);


Sound::Sound()
{
    
}

//void Sound::playSound(std::string file)
//{
//    const char* c = file.c_str();
//    wchar_t wstr[100] = { '\0', };
//    CharToWChar(c, wstr);
//    PlaySound(wstr, NULL, SND_FILENAME | SND_ASYNC); //일반 재생
//}

void playSound2(const char* file)
{
    mciOpen.lpstrElementName = wchar(LASER);
    mciOpen.lpstrDeviceType = L"WaveAudio";

    //mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);

    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
    dwID = mciOpen.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciOpen); //음악을 한 번 재생
    //Sleep(1000); //효과음이 재생될 때까지 정지했다가
    //mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL); //음원 재생 위치를 처음으로 초기화
}

void Sound::playSound(const char* file)
{
    sound_thread = new std::thread(playSound2, file);
    sound_thread->detach();
}

                                                                                                                                                                                                                                                        
// char to LPCWSTR
void Sound::CharToWChar(const char* pstrSrc, wchar_t pwstrDest[])
{
    int nLen = (int)strlen(pstrSrc) + 1; 
    mbstowcs(pwstrDest, pstrSrc, nLen);
}

wchar_t* wchar(const char* pstrSrc) {
    int nLen = (int)strlen(pstrSrc) + 1;
    wchar_t* dest = new wchar_t[nLen];
    mbstowcs(dest, pstrSrc, nLen);
    return dest;
}
