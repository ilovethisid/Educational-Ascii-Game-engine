#include "sound.h"

Sound::Sound()
{
    
}

void Sound::playSound(std::string file)
{
    const char* c = file.c_str();
    wchar_t wstr[100] = {'\0', };
    CharToWChar(c, wstr);
<<<<<<< HEAD
    PlaySound(wstr, NULL, SND_FILENAME | SND_ASYNC); //老馆 犁积
=======
  //  PlaySound(wstr, NULL, SND_FILENAME | SND_ASYNC); //老馆 犁积
>>>>>>> dc16fd8eafb1bdf9f91a7a7a64972654b540b18a
}
                                                                                                                                                                                                                                                        
// char to LPCWSTR
void Sound::CharToWChar(const char* pstrSrc, wchar_t pwstrDest[])
{
    int nLen = (int)strlen(pstrSrc) + 1; 
    mbstowcs(pwstrDest, pstrSrc, nLen);
}                                                                                                                        