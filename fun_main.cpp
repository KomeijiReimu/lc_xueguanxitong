#include <iostream>
#include <fstream>
#include <conio.h>
#include <list>
#include "class_student.hpp"
#include "sleep_cls.hpp"

using namespace std;

fstream dat;
list<TmpDat> sort_list_stu;
list<TmpDat> list_student;
list<TmpDat>::iterator it;
MySleepCls Marisa;
void Student::start()
{
    while (1)
    {
        cle_ar();
        if (!init())
            break;
        if (!menu())
            break;
    }
    Marisa.my_cls();
    return;
}
bool Student::init()
{
    bool r = true;
    do
    {
        if (!check_file(dat_name))
        {
            cout << "注意：数据文件不存在！如果不是首次注册使用本系统，请注意数据是否被误删！\n";
            dat.open(dat_name, ios::out | ios::trunc);
            if (!dat.good())
            {
                cout << "创建数据文件失败！按任意键返回...\n";
                _getch();
                r = false;
                break;
            }
            else
                dat.close();
        }
        if (check_isfile_empty(dat_name))
        {
            cout << "数据文件为空！请先添加数据！\n按任意键继续...";
            _getch();
            break;
        }
        dat.open(dat_name, ios::in);
        if (!dat.good())
        {
            cout << "打开数据文件失败！按任意键返回...\n";
            cout << dat_name;
            _getch();
            r = false;
            break;
        }
        TmpDat tmp_dat;
        while (dat >> tmp_dat.Num >> tmp_dat.S_name >> tmp_dat.Score)
            sort_list_stu.push_back(tmp_dat);
    } while (0);
    dat.close();
    copy(sort_list_stu.begin(), sort_list_stu.end(), back_inserter(list_student));
    return r;
}
void Student::cle_ar()
{
    sort_list_stu.clear();
    list_student.clear();
    return;
}
bool Student::save()
{
    bool r = true;
    dat.open(dat_name, ios::out);
    do
    {
        if (!dat.good())
        {
            cout << "打开数据文件失败！按任意键返回...\n";
            _getch();
            r = false;
            break;
        }
        it = list_student.begin();
        while (it != list_student.end())
        {
            dat << it->Num << ' ' << it->S_name << ' ' << it->Score << '\n';
            it++;
        }
    } while (0);
    dat.close();
    return r;
}
int Student::menu()
{
    int n;
    Marisa.my_cls();
    cout << "\t\t\t**********欢迎来到学生信息管理系统**********" << '\n';
    cout << "\t\t\t你可以进行以下操作:" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             1   浏览所有信息             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             2   添加学生信息             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             3   修改学生信息             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             4   删除学生信息             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             5   统计学生数据             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             6   退出程序                 |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             0   退出当前账号             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t请选择【0-7】：";
    cin >> n;
    switch (n)
    {
    case 1:
        while (look_s())
            ;
        break;
    case 2:
        while (add_s())
            ;
        break;
    case 3:
        while (modify_s())
            ;
        break;
    case 4:
        while (del_s())
            ;
        break;
    case 5:
        while (count_s())
            ;
        break;
    case 6:
        exit(0);
        break;
    }
    return n;
}

int Student::look_s()
{
    Marisa.my_cls();
    cout << "\t\t\t请选择排序方法：\n";
    cout << "1.学号\n";
    cout << "2.姓名\n";
    cout << "3.分数\n";
    cout << "4.不排序\n";
    cout << "0.返回主菜单\n";
    int n;
    cin >> n;
    switch (n)
    {
    case 1:
        sort_list_stu.sort(by_num);
        show(true, 1);
        break;
    case 2:
        sort_list_stu.sort(by_name);
        show(true, 2);
        break;
    case 3:
        sort_list_stu.sort(by_score);
        show(true, 3);
        break;
    case 4:
        show(true, 0);
        break;
    }
    return n;
}
void Student::show(bool r, int n)
{
    if (n)
    {
        it = sort_list_stu.begin();
        cout << "学号\t\t姓名\t\t分数\t\t\n";
        while (it != sort_list_stu.end())
        {
            cout << it->Num << "\t\t" << it->S_name << "\t\t" << it->Score << "\t\t\n";
            it++;
        }
    }
    else
    {
        it = list_student.begin();
        cout << "学号\t\t姓名\t\t分数\n";
        while (it != list_student.end())
        {
            cout << it->Num << "\t\t" << it->S_name << "\t\t" << it->Score << "\t\t\n";
            it++;
        }
    }
    if (r)
    {
        cout << "\n按任意键返回...\n";
        _getch();
    }
    return;
}

int Student::add_s()
{
    int n = 1;
    TmpDat tmp_dat;
    while (1)
    {
        cout << "请输入学号：";
        cin >> tmp_dat.Num;
        if (check(tmp_dat.Num))
            cout << "学号已存在，请勿重复输入！\n";
        else
            break;
    }
    cout << "请输入姓名：";
    cin >> tmp_dat.S_name;
    cout << "请输入分数：";
    cin >> tmp_dat.Score;
    list_student.push_back(tmp_dat);
    do
    {
        if (!save())
        {
            cout << "\n添加失败！，按任意键返回...";
            n = 0;
            _getch();
            break;
        }
        show(false, 0);
        cout << "\n添加成功！\n";
        cout << "输入 “Y” 继续添加，任意输入结束添加  ";
        cin >> tmp;
        if (!(tmp == "Y" || tmp == "y"))
            n = 0;
    } while (0);
    return n;
}

bool Student::check(int number)
{
    bool r = false;
    it = list_student.begin();
    while (it != list_student.end())
    {
        if (it->Num == number)
        {
            r = true;
            break;
        }
        it++;
    }
    return r;
}

int Student::modify_s()
{

    int n = 1;
    int r = 0;
    int number;
    string name;
    double score;
    do
    {
        if (check_isfile_empty(dat_name))
        {
            n = 0;
            break;
        }
        show(false, 0);
        cout << "\n请输入要修改的学生的学号：";
        cin >> number;
        it = list_student.begin();
        while (it != list_student.end())
        {
            if (it->Num == number)
            {
                cout << "请输入学号：";
                cin >> number;
                cout << "请输入姓名：";
                cin >> name;
                cout << "请输入分数：";
                cin >> score;
                it->Num = number;
                it->S_name = name;
                it->Score = score;
                if (!save())
                {
                    cout << "\n修改失败！，按任意键返回...";
                    n = 0;
                    _getch();
                    break;
                }
                show(false, 0);
                cout << "\n修改成功！\n";
                r = 1;
                break;
            }
            it++;
        }
        if (n)
        {
            if (!r)
                cout << "学号不存在！请检查您输入的学号是否正确！\n";
            cout << "输入 “Y” 继续修改，任意输入结束修改  ";
            cin >> tmp;
            if (!(tmp == "Y" || tmp == "y"))
                n = 0;
        }
    } while (0);
    return n;
}
int Student::del_s()
{
    int n = 1;
    int r = 0;
    int number;
    do
    {
        if (check_isfile_empty(dat_name))
        {
            n = 0;
            break;
        }
        show(false, 0);
        cout << "\n请输入要删除的学生的学号：";
        cin >> number;
        it = list_student.begin();
        while (it != list_student.end())
        {
            if (it->Num == number)
            {
                list_student.erase(it);
                if (!save())
                {
                    cout << "\n删除失败！，按任意键返回...";
                    n = 0;
                    _getch();
                    break;
                }
                show(false, 0);
                cout << "\n删除成功！\n";
                r = 1;
                break;
            }
            it++;
        }
        if (n)
        {
            if (!r)
                cout << "学号不存在！请检查您输入的学号是否正确！\n";
            cout << "输入 “Y” 继续删除，任意输入结束删除  ";
            cin >> tmp;
            if (!(tmp == "Y" || tmp == "y"))
                n = 0;
        }
    } while (0);
    return n;
}

int Student::count_s()
{
    Marisa.my_cls();
    cout << "\t\t\t请选择要统计的信息：\n";
    cout << "1.总人数\n";
    cout << "2.平均分\n";
    cout << "0.返回主菜单\n";
    int n;
    int i = list_student.size();
    double sum = 0;
    cin >> n;
    it = list_student.begin();
    switch (n)
    {
    case 1:
        cout << "\t\t\t总人数为 " << i << "人\n";
        cout << "按任意键返回...";
        _getch();
        break;
    case 2:
        if (!i)
        {
            cout << "\t\t\t没有学生数据！\n";
            cout << "按任意键返回...";
            _getch();
            break;
        }
        while (it != list_student.end())
        {
            sum += it->Score;
            it++;
        }
        cout << "\t\t\t平均分为 " << sum / i << "分 \n";
        cout << "按任意键返回...";
        _getch();
    }
    return n;
}