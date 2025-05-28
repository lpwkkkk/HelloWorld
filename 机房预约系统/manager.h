#pragma once
#include <iostream>
#include "identity.h"
#include <string>
#include <fstream>
#include "globalFile.h"
#include <vector>
#include "student.h"
#include "student.cpp"
#include "teacher.h"
#include "teacher.cpp"
#include <algorithm>
#include "computerRoom.h"
using namespace std;

class Manager : public Identity
{
public:
    //默认构造
    Manager();

    //有参构造
    Manager(string name, string pwd);

    //菜单界面
    virtual void openMeun();

    //添加账号
    void addPerson();

    //查看账号
    void showPerson();

    //查看机房信息
    void showComputer();

    //清空预约记录
    void cleanFile();

    //检测重复 参数一 id号 参数二 检测类型
    bool checkRepeat(int id, int type);

    //初始化容器
    void initVector();

    //学生容器
    vector<Student>vStu;

    //老师容器
    vector<Teacher>vTea;

    //机房容器
    vector<ComputerRoom>vCom;
};