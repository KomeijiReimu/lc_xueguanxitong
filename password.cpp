#include <iostream>
#include "password.hpp"
#include "sleep_cls.hpp"
using namespace std;

// 直接对数组进行操作

MySleepCls Yukari;

void Password::key_start()
{
    int tmpc = 0;
    Last_password = 0;
    Passwording = 0; // 指针
    for (char *i = Final_password; *i != '\000'; *i++)
        *i = '\000';
    // 进入输入判断
    while (tmpc != _enter_) // 非回车
    {
        tmpc = Yukari.my_getch();
        switch (tmpc)
        {
        case _back_: // 回退键
            backspace(Final_password);
            break;
        case _enter_: // 回车键结束
            break;
        case _directon_: // 方向键，注意win32返回两次getch,linux返回三次
#ifdef _WIN32
            leftRight(Yukari.my_getch());

#else
            Yukari.my_getch();
            leftRight(Yukari.my_getch());
#endif
            break;
        default:
            if (Last_password != 200)
                ins(tmpc);
            break;
        }
    }
}

void Password::leftRight(int direction)
{                            // 方向键
    if (direction == _left_) // <-
        if (!(Passwording <= 0))
        {
            Passwording--;
            putchar('\b'); // 光标向左移动
        }
    if (direction == _rigth_) // ->
        if (!(Passwording >= Last_password))
        {
            Passwording++;
            putchar('*'); // 光标向右移动
        }
}

void Password::backspace(char *Lpw) // 传不传指针都可以(?)
{                                   // 退格
    if (Passwording)
    {
        for (int i = Passwording - 1; i < Last_password; i++)
            Lpw[i] = Lpw[i + 1];                // 后面的整体向前移动一位，覆盖掉当前删除的数
        Final_password[Last_password] = '\000'; // 干掉多余的最后一位
        Passwording--;
        Last_password--;
        do
        { // 下面这块也比较奇妙，莫名其妙就试出来了
            for (int i = 0; i <= Last_password; i++)
                putchar('\b');
            for (int i = 0; i <= Last_password; i++)
                putchar(' ');
            for (int i = 0; i <= Last_password; i++)
                putchar('\b');
            for (int i = 0; i < Last_password; i++)
                putchar('*');
            // 重新输出*,而且数量比之前少一个
            for (int i = 0; i < (Last_password - Passwording); i++)
                putchar('\b');
        } while (0); // 这些是为了防止光标在中间时键入回退导致的显示错误
    }
}

void Password::ins(int t)
{ // 写入，最关键的一步
    Last_password++;
    if (Last_password > Passwording)
    {
        for (int i = Last_password; i >= Passwording; i--)
            Final_password[i] = Final_password[i - 1];
    }
    Final_password[Passwording] = t;
    Passwording++;
    for (int i = 0; i <= (Last_password - Passwording); i++)
        putchar('*');
    for (int i = 0; i < (Last_password - Passwording); i++)
        putchar('\b');
    // 这两步保证了输入之后光标位置不变，反正这样试出来就对
}