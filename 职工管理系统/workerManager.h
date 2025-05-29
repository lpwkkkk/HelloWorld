#pragma once //防止头文件重复包含
#include <iostream>//包含输入输出流头文件
using namespace std;//使用标准命名空间
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"


#include <fstream>
#define FILENAME "empFile.txt"



class WorkerManager
{
public:

    WorkerManager();//构造函数

    //展示菜单
    void ShowMenu();

    //退出
    void ExitSystem();

    //增加员工

    //1.记录职工人数
    int m_EmpNum;

    //2.记录职工数组指针
    Worker ** m_EmpArray;

    //3.添加职工函数
    void AddEmp();

    //保存文件
    void save();

    //判断文件是否为空
    bool m_FileIsEmpty;

    //统计文件中人数
    int get_EmpNum();

    //初始化员工
    void init_Emp();

    //显示职工
    void ShowEmp();

    //判断职工是否存在
    int IsExist(int id); 

    //删除职工
    void DelEmp();

    //修改职工
    void ModEmp();

    //查找职工
    void FindEmp();

    //排序
    void SortEmp();

    //清空文件
    void CleanFile();

    //析构函数
    ~WorkerManager();

};

