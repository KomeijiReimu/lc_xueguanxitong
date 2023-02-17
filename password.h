#pragma once

class Password
{
    void leftRight(int), backspace(char *), ins(int);

public:
    void key_start();
    char Final_password[200] = {'\000'}; // 最终密码
    int Last_password = 0;               // 密码最后一位的指针
    int Passwording = 0;                 // 密码当前指针
};
