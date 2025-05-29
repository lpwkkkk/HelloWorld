#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Manager :public Worker
{
public:
    //构造函数
    Manager(int id, string name, int did);
    //展示信息
    virtual void showInfo();

    //获取岗位名称
    virtual string getDeptName();
};