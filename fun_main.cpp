#include <iostream>
#include <fstream>
#include <list>
#include <string.h>
#include <string>
#include "sleep_cls.hpp"
#include "class_student.hpp"

using namespace std;

void print_find(list<TmpDat> &ll);
fstream dat;
list<TmpDat> sort_list_stu;
list<TmpDat> list_student;
list<TmpDat>::iterator it;
MySleepCls Marisa;
string a_s = "学号", b_s = "姓名", c_s = "分数";

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
                Marisa.my_getch();
                r = false;
                break;
            }
            else
                dat.close();
        }
        if (check_isfile_empty(dat_name))
        {
            cout << "数据文件为空！请先添加数据！\n按任意键继续...";
            Marisa.my_getch();
            break;
        }
        dat.open(dat_name, ios::in);
        if (!dat.good())
        {
            cout << "打开数据文件失败！按任意键返回...\n";
            cout << dat_name;
            Marisa.my_getch();
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
            Marisa.my_getch();
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
    string tmp_n;
    while (1)
    {
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
        cout << "\t\t\t|             5   查找学生信息             |" << '\n';
        cout << "\t\t\t|------------------------------------------|" << '\n';
        cout << "\t\t\t|             6   统计学生数据             |" << '\n';
        cout << "\t\t\t|------------------------------------------|" << '\n';
        cout << "\t\t\t|             7   关闭学管系统             |" << '\n';
        cout << "\t\t\t|------------------------------------------|" << '\n';
        cout << "\t\t\t|             0   退出当前账号             |" << '\n';
        cout << "\t\t\t|------------------------------------------|" << '\n';
        cout << "\t\t\t请选择【0-7】：";
        cin >> tmp_n;
        if (check_is_num(tmp_n))
            break;
    }
    n = stoi(tmp_n);
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
        while (find_s())
            ;
        break;
    case 6:
        while (count_s())
            ;
        break;
    case 7:
        exit(0);
        break;
    }
    return n;
}

int Student::look_s()
{
    int n;
    string tmp_n;
    while (1)
    {
        Marisa.my_cls();
        cout << "\t\t\t请选择排序方法：\n";
        cout << "1.学号\n";
        cout << "2.姓名\n";
        cout << "3.分数\n";
        cout << "4.不排序\n";
        cout << "0.返回主菜单\n";
        cin >> tmp_n;
        if (check_is_num(tmp_n))
            break;
    }
    n = stoi(tmp_n);
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
        printf("%20s%20s%20s\n", a_s.data(), b_s.data(), c_s.data());
        while (it != sort_list_stu.end())
        {
            printf("%20s%20s%20.2lf\n", it->Num.data(), it->S_name.data(), it->Score);
            it++;
        }
    }
    else
    {
        it = list_student.begin();
        printf("%20s%20s%20s\n", a_s.data(), b_s.data(), c_s.data());
        while (it != list_student.end())
        {
            printf("%20s%20s%20.2lf\n", it->Num.data(), it->S_name.data(), it->Score);
            it++;
        }
    }
    if (r)
    {
        cout << "\n按任意键返回...\n";
        Marisa.my_getch();
    }
    return;
}

int Student::add_s()
{
    string tmp_score;
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
    while (1)
    {
        cout << "请输入分数：";
        cin >> tmp_score;
        if (check_is_num(tmp_score))
            break;
        cout << "错误！输入的不是纯数字！请重新输入一个整数或小数！\n";
    }
    tmp_dat.Score = stod(tmp_score);
    list_student.push_back(tmp_dat);
    do
    {
        if (!save())
        {
            cout << "\n添加失败！，按任意键返回...";
            n = 0;
            Marisa.my_getch();
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

bool Student::check(string number)
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
    string number;
    string name;
    string tmp_score;
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
                while (1)
                {
                    cout << "请输入分数：";
                    cin >> tmp_score;
                    if (check_is_num(tmp_score))
                        break;
                    cout << "错误！输入的不是纯数字！请重新输入一个整数或小数！\n";
                }
                it->Num = number;
                it->S_name = name;
                it->Score = stod(tmp_score);
                if (!save())
                {
                    cout << "\n修改失败！，按任意键返回...";
                    n = 0;
                    Marisa.my_getch();
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
    string number;
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
                    Marisa.my_getch();
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

int Student::find_s()
{
    int n;
    string tmp_n;
    do
    {
        if (check_isfile_empty(dat_name))
        {
            n = 0;
            break;
        }
        while (1)
        {
            Marisa.my_cls();
            cout << "\t\t\t您希望以什么方式查找学生信息？请选择：\n";
            cout << "1.使用学号查找\n";
            cout << "2.使用姓名查找\n";
            cout << "3.查找某一分数段\n";
            cout << "0.返回主菜单\n";
            cin >> tmp_n;
            if (check_is_num(tmp_n))
                break;
        }
        n = stoi(tmp_n);
        switch (n)
        {
        case 1:
            find_bynum();
            break;
        case 2:
            find_byname();
            break;
        case 3:
            find_during();
            break;
        }
    } while (0);
    return n;
}

void Student::find_bynum()
{
    cout << "\n请输入要查找的学生的学号：";
    int r = 0;
    list<TmpDat> ll;
    string number;
    cin >> number;
    it = list_student.begin();
    while (it != list_student.end())
    {
        if (it->Num == number)
        {
            {
                ll.push_back(*it);
                r = 1;
                break;
            }
        }
        it++;
    }
    if (!r)
        cout << "学号不存在！请检查您输入的学号是否正确！\n";
    else
        print_find(ll);
    cout << "输入 “Y” 继续查找，任意输入结束查找  ";
    cin >> tmp;
    if (tmp == "Y" || tmp == "y")
        find_bynum();
    return;
}

void Student::find_byname()
{
    cout << "\n请输入要查找的学生的名字：";
    int r = 0;
    string name;
    list<TmpDat> ll;
    cin >> name;
    it = list_student.begin();
    while (it != list_student.end())
    {
        if (strstr(it->S_name.data(), name.data()))
        {
            ll.push_back(*it);
            r = 1;
        }
        it++;
    }
    if (!r)
        cout << "姓名不存在！请检查您输入的姓名是否正确！\n";
    else
        print_find(ll);
    cout << "输入 “Y” 继续查找，任意输入结束查找  ";
    cin >> tmp;
    if (tmp == "Y" || tmp == "y")
        find_byname();
    return;
}

void Student::find_during()
{
    double min, max;
    string tmp_score;
    list<TmpDat> ll;
    while (1)
    {
        while (1)
        {
            cout << "\n请确定要查询分数段的最小值：";
            cin >> tmp_score;
            if (!check_is_num(tmp_score))
            {
                cout << "错误！输入的不是纯数字！请重新输入一个整数或小数！\n";
                continue;
            }
            min = stod(tmp_score);
            cout << "\n请确定要查询分数段的最大值：";
            cin >> tmp_score;
            if (!check_is_num(tmp_score))
            {
                cout << "错误！输入的不是纯数字！请重新输入一个整数或小数！\n";
                continue;
            }
            max = stod(tmp_score);
            break;
        }
        if (min < max)
            break;
        else
            cout << "错误！您输入的最小值居然大于最大值！请检查后重新输入！\n";
    }
    it = list_student.begin();
    while (it != list_student.end())
    {
        if (it->Score >= min && it->Score <= max)
        {
            ll.push_back(*it);
        }
        it++;
    }
    if (!ll.size())
        cout << "该分数段没有学生信息！请重新确定范围：\n";
    else
        print_find(ll);
    cout << "输入 “Y” 继续查找，任意输入结束查找  ";
    cin >> tmp;
    if (tmp == "Y" || tmp == "y")
        find_during();
    return;
}

void print_find(list<TmpDat> &ll)
{
    list<TmpDat>::iterator p_it = ll.begin();
    cout << "查找结果：\n";
    printf("%20s%20s%20s\n", a_s.data(), b_s.data(), c_s.data());
    while (p_it != ll.end())
    {
        printf("%20s%20s%20.2lf\n", p_it->Num.data(), p_it->S_name.data(), p_it->Score);
        p_it++;
    }
    putchar('\n');
    return;
}

int Student::count_s()
{
    int n;
    double sum = 0;
    string tmp_n;
    int i = list_student.size();
    it = list_student.begin();
    while (1)
    {
        Marisa.my_cls();
        cout << "\t\t\t请选择要统计的信息：\n";
        cout << "1.总人数\n";
        cout << "2.平均分\n";
        cout << "0.返回主菜单\n";
        cin >> tmp_n;
        if (check_is_num(tmp_n))
            break;
    }
    n = stoi(tmp_n);
    switch (n)
    {
    case 1:
        cout << "\t\t\t总人数为 " << i << "人\n";
        cout << "按任意键返回...";
        Marisa.my_getch();
        break;
    case 2:
        if (!i)
        {
            cout << "\t\t\t没有学生数据！\n";
            cout << "按任意键返回...";
            Marisa.my_getch();
            break;
        }
        while (it != list_student.end())
        {
            sum += it->Score;
            it++;
        }
        cout << "\t\t\t平均分为 " << sum / i << "分 \n";
        cout << "按任意键返回...";
        Marisa.my_getch();
    }
    return n;
}

bool Student::check_is_num(string &str)
{
    bool r = true;
    int n = 0;
    for (int i = 0; i < str.size(); i++)
    {
        int tmp = (int)str[i];
        if (tmp >= 48 && tmp <= 57)
        {
            continue;
        }
        else
        {
            if (n == 0 && i != 0 && i != str.size() - 1)
            {
                if (tmp == 46)
                {
                    n++;
                    continue;
                }
            }
            r = false;
            break;
        }
    }
    return r;
}
