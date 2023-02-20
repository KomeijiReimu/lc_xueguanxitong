#include <iostream>
#include <fstream>
#include <conio.h>
#include <map>
#include "sleep_cls.hpp"
#include "class_student.hpp"
#include "password.hpp"
#include "md5.hpp"

using namespace std;

Password ps;
fstream key;
MySleepCls Koishi;
map<string, string> login;
map<string, string>::iterator key_it;

int Student::welcome()
{
    if (check_isfile_empty(KEY))
    {
        cout << "用户密码存储文件信息缺失，即将被迫回档，重新注册！\n***您可能会失去已有数据***\n按任意键继续... ";
        _getch();
        Koishi.my_cls();
        re_gister(true);
        return 0;
    }
    else
    {
        key.close();
        cout << "请选择：登录已有账户（1）或创建新账户（2）：\n";
        while (1)
        {
            cin >> tmp;
            if (tmp == "1")
                break;
            else if (tmp == "2")
            {
                re_gister(false);
                return 0;
            }
            else
                continue;
        }
        lo_ad();
        return 1;
    }
}
void Student::welcome2()
{
    for (char *i = weltxt3; *i != '\000'; *i++)
    {
        putchar(*i);
        Koishi.my_sleep(8);
    }
    _getch();
    re_gister(true);
    return;
}
void Student::re_gister(bool n_ew)
{
    if (n_ew)
    {
        key.open(KEY, ios::out | ios::trunc);
        key.close();
        if (!check_file(KEY))
        {
            cout << "\n创建用户配置文件失败！\n按任意键返回...";
            _getch();
            return;
        }
    }
    else if (!key_load())
    {
        _getch();
        return;
    }
    while (1)
    {
        cout << "请创建您的的用户名（技术所限，请不要带空格）：\n";
        cin >> ID;
        if (login.find(ID) != login.end())
        {
            cout << "该用户名已存在，请重新选择另一个用户名（1）或者修改登录密码（2）";
            cin >> tmp;
            if (tmp == "2")
            {
                key_it = login.find(ID);
                cout << "请输入旧密码：\n";
                while (1)
                {
                    do
                    {
                        ps.key_start();
                        p_password = ps.Final_password;
                    } while (p_password == "\000");
                    password = MD5(p_password).toStr();
                    if (password == key_it->second)
                    {
                        cout << "\n请输入新密码：（请不要带空格）\n";
                        break;
                    }
                    else
                    {
                        cout << "\n密码错误！请重试： \n";
                        continue;
                    }
                }
                do
                {
                    ps.key_start();
                    password = ps.Final_password;
                } while (password == "\000");
                password = MD5(ps.Final_password).toStr();
                key_it->second = password;
                if (!key_save())
                {
                    _getch();
                    return;
                }
                cout << "\n修改密码成功！即将返回初始界面！\n 按任意键继续...";
                _getch();
                Koishi.my_cls();
                return;
            }
            else
                continue;
        }
        else
        {
            cout << "请为您的账户创建一个密码（请不要带空格）\n";
            ps.key_start();
            password = MD5(ps.Final_password).toStr();
            login.insert({ID, password});
            if (!key_save())
            {
                _getch();
                return;
            }
            Koishi.my_cls();

            for (int i = 3; i > 0; i--)
            {
                cout << "\t\t\t账户已创建完成，请登录。\n";
                cout << "\t\t\t" << i << "秒后返回到主页面……" << endl;
                Koishi.my_sleep(1000);
                Koishi.my_cls();
            }
            return;
        }
    }
}
void Student::lo_ad()
{
    if (!key_load())
    {
        _getch();
        return;
    }
    for (char *i = weltxt1; *i != '\000'; *i++)
    {
        putchar(*i);
        Koishi.my_sleep(8);
    }
    while (1)
    {
        do
        {
            cin >> ID;
        } while (ID == "\000");
        key_it = login.find(ID);
        if (key_it == login.end())
        {
            cout << "用户名不存在！请重新输入： \n";
            continue;
        }
        else
            break;
    }
    for (char *i = weltxt2; *i != '\000'; *i++)
    {
        putchar(*i);
        Koishi.my_sleep(8);
    }
    while (1)
    {
        do
        {
            ps.key_start();
            password = ps.Final_password;
        } while (password == "\000");
        password = MD5(ps.Final_password).toStr();
        if (password == key_it->second)
            break;
        else
        {
            cout << "\n密码错误！请重新输入：\n";
            continue;
        }
    }
    Koishi.my_cls();
    for (int i = 3; i > 0; i--)
    {
        cout << "\t\t\t登陆成功！\n";
        cout << "\t\t\t" << i << "秒后将进入系统……" << endl;
        Koishi.my_sleep(1000);
        Koishi.my_cls();
    }
    dat_name = ID + ".dat";
    return;
}

bool Student::key_load()
{
    bool r_key_load = true;
    key.open(KEY, ios::in);
    do
    {
        if (!key.good())
        {
            cout << "用户配置文件打开失败，请重试！\n按任意键返回...\n";
            r_key_load = false;
            break;
        }
        while (key >> a >> b)
            login.insert({a, b});
    } while (0);
    key.close();
    return r_key_load;
}
bool Student::key_save()
{
    bool r_key_save = true;
    key.open(KEY, ios::out);
    do
    {
        if (!key.good())
        {
            r_key_save = false;
            cout << "密码保存失败，请重试！\n按任意键返回...\n";
            break;
        }
        for (key_it = login.begin(); key_it != login.end(); key_it++)
        {
            key << key_it->first << " ";
            key << key_it->second << '\n';
        }
    } while (0);
    key.close();
    return r_key_save;
}
bool Student::check_file(string file_name)
{
    fstream fs;
    bool r;
    fs.open(file_name, ios::in);
    if (fs.good())
        r = true;
    else
        r = false;
    fs.close();
    return r;
}
bool Student::check_isfile_empty(string file_name)
{
    int n = 0;
    fstream fs;
    bool r;
    fs.open(file_name, ios::in);
    while (getline(fs, tmp))
    {
        n++;
    }
    fs.close();
    if (n == 0)
        r = true;
    else
        r = false;
    return r;
}