#pragma once
#include <iostream>
#include <string>
using namespace std;

//职工抽象类
class Worker
{
public:

    //展示信息
    virtual void showInfo() = 0;

    //获取岗位名称
    virtual string getDeptName() = 0; 

    //员工编号
    int m_Id;
    //员工姓名
    string m_name;
    //权限编号
    int m_DeptId;
};