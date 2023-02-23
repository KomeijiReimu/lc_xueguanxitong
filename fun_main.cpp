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
string a_s = "ѧ��", b_s = "����", c_s = "����";

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
                Marisa.my_getch();
                r = false;
                break;
            }
            else
                dat.close();
        }
        if (check_isfile_empty(dat_name))
        {
            cout << "�����ļ�Ϊ�գ�����������ݣ�\n�����������...";
            Marisa.my_getch();
            break;
        }
        dat.open(dat_name, ios::in);
        if (!dat.good())
        {
            cout << "�������ļ�ʧ�ܣ������������...\n";
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
            cout << "�������ļ�ʧ�ܣ������������...\n";
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
        cout << "\t\t\t|             5   ����ѧ����Ϣ             |" << '\n';
        cout << "\t\t\t|------------------------------------------|" << '\n';
        cout << "\t\t\t|             6   ͳ��ѧ������             |" << '\n';
        cout << "\t\t\t|------------------------------------------|" << '\n';
        cout << "\t\t\t|             7   �ر�ѧ��ϵͳ             |" << '\n';
        cout << "\t\t\t|------------------------------------------|" << '\n';
        cout << "\t\t\t|             0   �˳���ǰ�˺�             |" << '\n';
        cout << "\t\t\t|------------------------------------------|" << '\n';
        cout << "\t\t\t��ѡ��0-7����";
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
        cout << "\t\t\t��ѡ�����򷽷���\n";
        cout << "1.ѧ��\n";
        cout << "2.����\n";
        cout << "3.����\n";
        cout << "4.������\n";
        cout << "0.�������˵�\n";
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
        cout << "\n�����������...\n";
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
        cout << "������ѧ�ţ�";
        cin >> tmp_dat.Num;
        if (check(tmp_dat.Num))
            cout << "ѧ���Ѵ��ڣ������ظ����룡\n";
        else
            break;
    }

    cout << "������������";
    cin >> tmp_dat.S_name;
    while (1)
    {
        cout << "�����������";
        cin >> tmp_score;
        if (check_is_num(tmp_score))
            break;
        cout << "��������Ĳ��Ǵ����֣�����������һ��������С����\n";
    }
    tmp_dat.Score = stod(tmp_score);
    list_student.push_back(tmp_dat);
    do
    {
        if (!save())
        {
            cout << "\n���ʧ�ܣ��������������...";
            n = 0;
            Marisa.my_getch();
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
                while (1)
                {
                    cout << "�����������";
                    cin >> tmp_score;
                    if (check_is_num(tmp_score))
                        break;
                    cout << "��������Ĳ��Ǵ����֣�����������һ��������С����\n";
                }
                it->Num = number;
                it->S_name = name;
                it->Score = stod(tmp_score);
                if (!save())
                {
                    cout << "\n�޸�ʧ�ܣ��������������...";
                    n = 0;
                    Marisa.my_getch();
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
    string number;
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
                    Marisa.my_getch();
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
            cout << "\t\t\t��ϣ����ʲô��ʽ����ѧ����Ϣ����ѡ��\n";
            cout << "1.ʹ��ѧ�Ų���\n";
            cout << "2.ʹ����������\n";
            cout << "3.����ĳһ������\n";
            cout << "0.�������˵�\n";
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
    cout << "\n������Ҫ���ҵ�ѧ����ѧ�ţ�";
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
        cout << "ѧ�Ų����ڣ������������ѧ���Ƿ���ȷ��\n";
    else
        print_find(ll);
    cout << "���� ��Y�� �������ң����������������  ";
    cin >> tmp;
    if (tmp == "Y" || tmp == "y")
        find_bynum();
    return;
}

void Student::find_byname()
{
    cout << "\n������Ҫ���ҵ�ѧ�������֣�";
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
        cout << "���������ڣ�����������������Ƿ���ȷ��\n";
    else
        print_find(ll);
    cout << "���� ��Y�� �������ң����������������  ";
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
            cout << "\n��ȷ��Ҫ��ѯ�����ε���Сֵ��";
            cin >> tmp_score;
            if (!check_is_num(tmp_score))
            {
                cout << "��������Ĳ��Ǵ����֣�����������һ��������С����\n";
                continue;
            }
            min = stod(tmp_score);
            cout << "\n��ȷ��Ҫ��ѯ�����ε����ֵ��";
            cin >> tmp_score;
            if (!check_is_num(tmp_score))
            {
                cout << "��������Ĳ��Ǵ����֣�����������һ��������С����\n";
                continue;
            }
            max = stod(tmp_score);
            break;
        }
        if (min < max)
            break;
        else
            cout << "�������������Сֵ��Ȼ�������ֵ��������������룡\n";
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
        cout << "�÷�����û��ѧ����Ϣ��������ȷ����Χ��\n";
    else
        print_find(ll);
    cout << "���� ��Y�� �������ң����������������  ";
    cin >> tmp;
    if (tmp == "Y" || tmp == "y")
        find_during();
    return;
}

void print_find(list<TmpDat> &ll)
{
    list<TmpDat>::iterator p_it = ll.begin();
    cout << "���ҽ����\n";
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
        cout << "\t\t\t��ѡ��Ҫͳ�Ƶ���Ϣ��\n";
        cout << "1.������\n";
        cout << "2.ƽ����\n";
        cout << "0.�������˵�\n";
        cin >> tmp_n;
        if (check_is_num(tmp_n))
            break;
    }
    n = stoi(tmp_n);
    switch (n)
    {
    case 1:
        cout << "\t\t\t������Ϊ " << i << "��\n";
        cout << "�����������...";
        Marisa.my_getch();
        break;
    case 2:
        if (!i)
        {
            cout << "\t\t\tû��ѧ�����ݣ�\n";
            cout << "�����������...";
            Marisa.my_getch();
            break;
        }
        while (it != list_student.end())
        {
            sum += it->Score;
            it++;
        }
        cout << "\t\t\tƽ����Ϊ " << sum / i << "�� \n";
        cout << "�����������...";
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
