#pragma once
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#endif

#ifdef _WIN32
const int _back_ = 0x08;
const int _del_ = 0x2e;
const int _enter_ = 0x0d;
const int _directon_ = 0xe0;
const int _left_ = 0x4b;
const int _rigth_ = 0x4d;

#else
const int _back_ = 127;
const int _del_ = 27;
const int _enter_ = 10;
const int _directon_ = 27;
const int _left_ = 67;
const int _rigth_ = 68;

#endif

class MySleepCls
{
public:
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
    int my_getch()
    {
#ifdef _WIN32
        return _getch();
#else

        struct termios oldt,
            newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;

#endif
    }
};