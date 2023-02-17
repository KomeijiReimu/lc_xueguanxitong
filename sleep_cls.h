#pragma once
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
void my_sleep(unsigned int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void my_cls()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
