#include <iostream>
#include <fstream>
#include "class_student.h"
// �������⣺�������sleep_cls.h�ᱨ��
// ��¼����֧��linux��������������sleep_cls.h��ֻ֧��win32

// ֧�ֶ��û���¼���޸��˺�����
// V1.0.1
using namespace std;
int main()
{
    student st;
    while (1)
    {
        if (st.check_file(st.KEY))
        {
            if (st.welcome())
                st.start();
        }
        else
            st.welcome2();
    }
    return 0;
}