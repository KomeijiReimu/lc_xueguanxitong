#include <iostream>
#include <conio.h>
#include "password.hpp"
using namespace std;

// ֱ�Ӷ�������в���

void Password::key_start()
{
    int tmpc = 0;
    Last_password = 0;
    Passwording = 0; // ָ��
    for (char *i = Final_password; *i != '\000'; *i++)
        *i = '\000';
    // ���������ж�
    while (tmpc != 0x0d) // �ǻس�
    {
        tmpc = _getch();
        switch (tmpc)
        {
        case 0x08: // ���˼�
            backspace(Final_password);
            break;
        case 0x0d: // �س�������
            break;
        case 0xe0: // �������ע��ϵͳ��������getch
            leftRight(_getch());
            break;
        default:
            if (Last_password != 200)
                ins(tmpc);
            break;
        }
    }
}

void Password::leftRight(int direction)
{                          // �����
    if (direction == 0x4b) // <-
        if (!(Passwording <= 0))
        {
            Passwording--;
            putchar('\b'); // ��������ƶ�
        }
    if (direction == 0x4d) // ->
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
{                    // д�룬��ؼ���һ��
    Last_password++; // ���λ��++
    if (Last_password > Passwording)
    {
        for (int i = Last_password; i >= Passwording; i--)
            Final_password[i] = Final_password[i - 1]; // �Ѻ���ļ����ַ�ȫ������һλ,Ȼ�����ڵ�ǰλд�����ַ�
    }
    Final_password[Passwording] = t; // д��
    Passwording++;                   // ָ��++
    for (int i = 0; i <= (Last_password - Passwording); i++)
        putchar('*');
    for (int i = 0; i < (Last_password - Passwording); i++)
        putchar('\b');
    // ��������֤������֮����λ�ò��䣬���������Գ����Ͷ�
}