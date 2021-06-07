#include "sound.h"

MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;
MCI_STATUS_PARMS   mciStatus; //������ ����

#define LASER "C:\\Users\\ilove\\source\\repos\\Educational-Ascii-Game-engine\\usrlib\\laser-gun.wav" // ȿ���� ��� ����


UINT wDeviceID = 0;



DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave)
{

    DWORD Result;


    mciOpen.lpstrDeviceType = L"WaveAudio";

    //WaveAudio ��� MPEGVideo�� ����ϸ� mp3 ������ ����մϴ�.


    mciOpen.lpstrElementName = lpszWave;

    Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);

    if (Result)
        return Result;

    wDeviceID = mciOpen.wDeviceID;

    mciOpen.dwCallback = (DWORD)hWnd;

    if (Result)
        return Result;


    return 0;
}


int dwID;

wchar_t* wchar(const char* pstrSrc);


Sound::Sound()
{

}

void Sound::playSound(std::string file)
{
    const char* c = file.c_str();
    wchar_t wstr[100] = {'\0', };
    CharToWChar(c, wstr);
    PlaySound(wstr, NULL, SND_FILENAME | SND_ASYNC); //�Ϲ� ���
}

void Sound::playSound2(const char* file)
{
    wchar_t laser[100] = { '\0', };
    CharToWChar(LASER, laser);
    mciOpen.lpstrElementName = laser;
    mciOpen.lpstrDeviceType = L"WaveAudio";
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
    dwID = mciOpen.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciOpen); //������ �� �� ���
    //Sleep(1000); //ȿ������ ����� ������ �����ߴٰ�
    //mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL); //���� ��� ��ġ�� ó������ �ʱ�ȭ
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
