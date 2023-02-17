#include <iostream>
#include <fstream>
#include "class_student.h"
// 存在问题：多次引用sleep_cls.h会报错
// 登录界面支持linux，主界面引不了sleep_cls.h，只支持win32

// 支持多用户登录，修改账号密码
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