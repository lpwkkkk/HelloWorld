#pragma once
#include <iostream>
#include "identity.h"
#include <string>
#include "orderFile.h"
#include <vector>
using namespace std;

class Teacher : public Identity
{
    public:
    //默认构造
    Teacher();

    //有参构造
    Teacher(int empId, string name, string pwd);

    //操作菜单  纯虚函数
    virtual void openMeun();

    //查看所有学生预约
    void showAllOeder();

    //审核所有预约
    void validOrder();

    //职工号
    int m_EmpId;
};
