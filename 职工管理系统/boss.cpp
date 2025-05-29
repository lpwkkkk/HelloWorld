#include <iostream>
#include "Boss.h"
using namespace std;

 //构造函数
 Boss::Boss(int id, string name, int did)
 {
    this->m_Id = id;
    this->m_name = name;
    this->m_DeptId = did;
 }
 //展示信息
 void  Boss::showInfo()
 {
    cout << "worker id  " << this->m_Id
         << "\t worker name  " << this->m_name
         << "\t department id      " << this->getDeptName()
         << "\t duty: play with secretary" << endl;
 }

 //获取岗位名称
string Boss::getDeptName()
{
    return string("boss");
}