#include <iostream>
using namespace std;
// #include  "workerManager.h"
#include "workerManager.cpp"

// #include "worker.h"
// #include "employee.h"
#include "employee.cpp"
#include "manager.cpp"
#include "boss.cpp"
int main() 
{
//     //测试代码
//     Worker * worker = NULL;
//     worker = new Employee(1, "zhangsan",1);
//     worker->showInfo();
//     delete worker;

//     worker = new Manager(2, "lisi", 2);
//     worker->showInfo();
//     delete worker;

//     worker = new Boss(3, "wangwu", 3);
//     worker->showInfo();
//     delete worker;

    //实列化管理者对象
    WorkerManager wm;

    int choice = 0;//存储选项

    while(true)
    {
        //调用成员函数
        wm.ShowMenu();

        cout <<"write your choice" << endl;
        cin >> choice;//接受用户选择

        switch(choice)
        {
            case 0:   //退出系统
                wm.ExitSystem();
                break;
            case 1:   //增加员工
                wm.AddEmp();
                break;
            case 2:   //显示员工
                wm.ShowEmp();
                break;
            case 3:   //删除员工
                wm.DelEmp();
                break;
            case 4:   //修改员工
                wm.ModEmp();
                break;
            case 5:   //查找员工
                wm.FindEmp();
                break;
            case 6:   //排序
                wm.SortEmp();
                break;
            case 7:   //清空文档
                wm.CleanFile();
                break; 
            default:
                system("cls");//清屏
        }

    }

    
            
    system("pause");
    return 0;
}