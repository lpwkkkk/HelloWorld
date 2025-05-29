#include <iostream>
#include "manager.h"
using namespace std;

 //构造函数
 Manager::Manager(int id, string name, int did)
 {
    this->m_Id = id;
    this->m_name = name;
    this->m_DeptId = did;
 }
 //展示信息
 void  Manager::showInfo()
 {
    cout << "worker id  " << this->m_Id
         << "\t worker name  " << this->m_name
         << "\t department id   " << this->getDeptName()
         << "\t duty:finish task from boss and get to employees " << endl;
 }

 //获取岗位名称
string Manager::getDeptName()
{
    return string("manager");
}