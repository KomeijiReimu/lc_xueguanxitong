#include <iostream>
#include "password.hpp"
#include "sleep_cls.hpp"
using namespace std;

// ֱ�Ӷ�������в���

MySleepCls Yukari;

void Password::key_start()
{
    int tmpc = 0;
    Last_password = 0;
    Passwording = 0; // ָ��
    for (char *i = Final_password; *i != '\000'; *i++)
        *i = '\000';
    // ���������ж�
    while (tmpc != _enter_) // �ǻس�
    {
        tmpc = Yukari.my_getch();
        switch (tmpc)
        {
        case _back_: // ���˼�
            backspace(Final_password);
            break;
        case _enter_: // �س�������
            break;
        case _directon_: // �������ע��win32��������getch,linux��������
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
{                            // �����
    if (direction == _left_) // <-
        if (!(Passwording <= 0))
        {
            Passwording--;
            putchar('\b'); // ��������ƶ�
        }
    if (direction == _rigth_) // ->
        if (!(Passwording >= Last_password))
        {
            Passwording++;
            putchar('*'); // ��������ƶ�
        }
}

void Password::backspace(char *Lpw) // ������ָ�붼����(?)
{                                   // �˸�
    if (Passwording)
    {
        for (int i = Passwording - 1; i < Last_password; i++)
            Lpw[i] = Lpw[i + 1];                // �����������ǰ�ƶ�һλ�����ǵ���ǰɾ������
        Final_password[Last_password] = '\000'; // �ɵ���������һλ
        Passwording--;
        Last_password--;
        do
        { // �������Ҳ�Ƚ����Ī��������Գ�����
            for (int i = 0; i <= Last_password; i++)
                putchar('\b');
            for (int i = 0; i <= Last_password; i++)
                putchar(' ');
            for (int i = 0; i <= Last_password; i++)
                putchar('\b');
            for (int i = 0; i < Last_password; i++)
                putchar('*');
            // �������*,����������֮ǰ��һ��
            for (int i = 0; i < (Last_password - Passwording); i++)
                putchar('\b');
        } while (0); // ��Щ��Ϊ�˷�ֹ������м�ʱ������˵��µ���ʾ����
    }
}

void Password::ins(int t)
{ // д�룬��ؼ���һ��
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
    // ��������֤������֮����λ�ò��䣬���������Գ����Ͷ�
}