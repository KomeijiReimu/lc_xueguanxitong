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
            cout << "ע�⣺�����ļ������ڣ���������״�ע��ʹ�ñ�ϵͳ����ע�������Ƿ���ɾ��\n";
            dat.open(dat_name, ios::out | ios::trunc);
            if (!dat.good())
            {
                cout << "���������ļ�ʧ�ܣ������������...\n";
                _getch();
                r = false;
                break;
            }
            else
                dat.close();
        }
        if (check_isfile_empty(dat_name))
        {
            cout << "�����ļ�Ϊ�գ�����������ݣ�\n�����������...";
            _getch();
            break;
        }
        dat.open(dat_name, ios::in);
        if (!dat.good())
        {
            cout << "�������ļ�ʧ�ܣ������������...\n";
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
            cout << "�������ļ�ʧ�ܣ������������...\n";
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
    cout << "\t\t\t**********��ӭ����ѧ����Ϣ����ϵͳ**********" << '\n';
    cout << "\t\t\t����Խ������²���:" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             1   ���������Ϣ             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             2   ���ѧ����Ϣ             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             3   �޸�ѧ����Ϣ             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             4   ɾ��ѧ����Ϣ             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             5   ͳ��ѧ������             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             6   �˳�����                 |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t|             0   �˳���ǰ�˺�             |" << '\n';
    cout << "\t\t\t|------------------------------------------|" << '\n';
    cout << "\t\t\t��ѡ��0-7����";
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
    cout << "\t\t\t��ѡ�����򷽷���\n";
    cout << "1.ѧ��\n";
    cout << "2.����\n";
    cout << "3.����\n";
    cout << "4.������\n";
    cout << "0.�������˵�\n";
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
        cout << "ѧ��\t\t����\t\t����\t\t\n";
        while (it != sort_list_stu.end())
        {
            cout << it->Num << "\t\t" << it->S_name << "\t\t" << it->Score << "\t\t\n";
            it++;
        }
    }
    else
    {
        it = list_student.begin();
        cout << "ѧ��\t\t����\t\t����\n";
        while (it != list_student.end())
        {
            cout << it->Num << "\t\t" << it->S_name << "\t\t" << it->Score << "\t\t\n";
            it++;
        }
    }
    if (r)
    {
        cout << "\n�����������...\n";
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
        cout << "������ѧ�ţ�";
        cin >> tmp_dat.Num;
        if (check(tmp_dat.Num))
            cout << "ѧ���Ѵ��ڣ������ظ����룡\n";
        else
            break;
    }
    cout << "������������";
    cin >> tmp_dat.S_name;
    cout << "�����������";
    cin >> tmp_dat.Score;
    list_student.push_back(tmp_dat);
    do
    {
        if (!save())
        {
            cout << "\n���ʧ�ܣ��������������...";
            n = 0;
            _getch();
            break;
        }
        show(false, 0);
        cout << "\n��ӳɹ���\n";
        cout << "���� ��Y�� ������ӣ���������������  ";
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
        cout << "\n������Ҫ�޸ĵ�ѧ����ѧ�ţ�";
        cin >> number;
        it = list_student.begin();
        while (it != list_student.end())
        {
            if (it->Num == number)
            {
                cout << "������ѧ�ţ�";
                cin >> number;
                cout << "������������";
                cin >> name;
                cout << "�����������";
                cin >> score;
                it->Num = number;
                it->S_name = name;
                it->Score = score;
                if (!save())
                {
                    cout << "\n�޸�ʧ�ܣ��������������...";
                    n = 0;
                    _getch();
                    break;
                }
                show(false, 0);
                cout << "\n�޸ĳɹ���\n";
                r = 1;
                break;
            }
            it++;
        }
        if (n)
        {
            if (!r)
                cout << "ѧ�Ų����ڣ������������ѧ���Ƿ���ȷ��\n";
            cout << "���� ��Y�� �����޸ģ�������������޸�  ";
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
        cout << "\n������Ҫɾ����ѧ����ѧ�ţ�";
        cin >> number;
        it = list_student.begin();
        while (it != list_student.end())
        {
            if (it->Num == number)
            {
                list_student.erase(it);
                if (!save())
                {
                    cout << "\nɾ��ʧ�ܣ��������������...";
                    n = 0;
                    _getch();
                    break;
                }
                show(false, 0);
                cout << "\nɾ���ɹ���\n";
                r = 1;
                break;
            }
            it++;
        }
        if (n)
        {
            if (!r)
                cout << "ѧ�Ų����ڣ������������ѧ���Ƿ���ȷ��\n";
            cout << "���� ��Y�� ����ɾ���������������ɾ��  ";
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
    cout << "\t\t\t��ѡ��Ҫͳ�Ƶ���Ϣ��\n";
    cout << "1.������\n";
    cout << "2.ƽ����\n";
    cout << "0.�������˵�\n";
    int n;
    int i = list_student.size();
    double sum = 0;
    cin >> n;
    it = list_student.begin();
    switch (n)
    {
    case 1:
        cout << "\t\t\t������Ϊ " << i << "��\n";
        cout << "�����������...";
        _getch();
        break;
    case 2:
        if (!i)
        {
            cout << "\t\t\tû��ѧ�����ݣ�\n";
            cout << "�����������...";
            _getch();
            break;
        }
        while (it != list_student.end())
        {
            sum += it->Score;
            it++;
        }
        cout << "\t\t\tƽ����Ϊ " << sum / i << "�� \n";
        cout << "�����������...";
        _getch();
    }
    return n;
}