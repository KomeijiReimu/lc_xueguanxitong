#pragma once

class TmpDat
{
public:
    std::string Num;
    std::string S_name;
    double Score;
};

class Student
{
public:
    bool check_file(std::string);
    int welcome();
    void welcome2();
    void start();
    std::string KEY = "key.ini";

private:
    bool check_isfile_empty(std::string);
    void re_gister(bool);
    void lo_ad();
    bool key_load();
    bool key_save();
    bool init();
    void cle_ar();
    bool save();
    int menu();
    int look_s();
    int add_s();
    int del_s();
    int modify_s();
    int find_s();
    void find_bynum();
    void find_byname();
    void find_during();
    int count_s();
    void show(bool, int);
    bool check(std::string);
    bool check_is_num(std::string &str);

    static bool by_num(TmpDat a, TmpDat b)
    {
        return a.Num < b.Num;
    }

    static bool by_name(TmpDat a, TmpDat b)
    {
        return (a.S_name.compare(b.S_name)) < 0;
    }

    static bool by_score(TmpDat a, TmpDat b)
    {
        return (a.Score != b.Score ? a.Score > b.Score : a.Score < b.Score);
    }

    std::string a, b;
    std::string ID, password, p_password;

    char weltxt1[1000] = "��ӭ��ʹ�ñ���ѧ����Ϣ����ϵͳ�����������·����������û�����������е�¼\n\n�����������û���:  \n";
    char weltxt2[1000] = "���������룺 \n";
    char weltxt3[1000] = "��ӭ���״�ʹ�ñ���ѧ����Ϣ����ϵͳ������������һ���û�����������ʹ�ñ�ϵͳ��\n\n�밴���������...  \n";

    std::string tmp;
    std::string dat_name;
};