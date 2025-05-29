#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Boss :public Worker
{
public:
    //构造函数
    Boss(int id, string name, int did);
    //展示信息
    virtual void showInfo();

    //获取岗位名称
    virtual string getDeptName();
};