#include <iostream>
#include <fstream>
#include "class_student.hpp"

// ���ߣ����
// ֧�ֶ��û���¼���޸��˺�����
// V1.0.2

using namespace std;
int main()
{
    Student st;
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