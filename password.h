#pragma once

class Password
{
    void leftRight(int), backspace(char *), ins(int);

public:
    void key_start();
    char Final_password[200] = {'\000'}; // ��������
    int Last_password = 0;               // �������һλ��ָ��
    int Passwording = 0;                 // ���뵱ǰָ��
};
