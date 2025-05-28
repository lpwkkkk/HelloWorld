#include <iostream>
using namespace std;
#include "Identity.h"
#include <fstream>
#include <string>
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.cpp"
#include "orderFile.cpp"


//进入教师子菜单页面
void teacherMenu(Identity * &teacher)
{
    while(true)
    {
        //调用子菜单界面
        teacher->openMeun();

        Teacher * tea = (Teacher *)teacher;

        int select = 0;//接受用户选择

        cin >> select;

        if(select == 1)//查看所有预约
        {
            tea->showAllOeder();
        }
        else if(select == 2)//审核预约
        {
            tea->validOrder();
        }
        else if(select == 0)
        {
            cout << "ESC";
            delete &teacher;
            system("pause");
            system("cls");
        }
        else
        {
            cout << "Input error try again" << endl;
        }

    }
}

//进入学生子菜单页面
void studentMenu(Identity * &student)
{
    while(true)
    {
        //调用学生子菜单
        student->openMeun();

        Student * stu = (Student *)student;

        int select = 0;
        cin >> select;//接受用户选择

        if(select == 1)//申请
        {
            stu->applyOrder();
        }
        else if(select == 2) //查看自身预约
        {
            stu->showMyOrder();
        }
        else if(select == 3) //查看所有预约
        {
            stu->showAllOrder();
        }
        else if(select == 4) //取消预约
        {
            stu->cancelOrder();
        }
        else //注销登录
        {
            cout << "ESC" << endl;
            delete &student;
            system("pause");
            system("cls");
        }

    }
}

//进入管理员子菜单
void managerMeun(Identity * &manager)
{
    while(true)
    {
        //调用管理员子菜单
        manager->openMeun();

        //将父类指针转为子类指针，调用子类特有接口
        Manager *man = (Manager*)manager;

        int select = 0;
        //接受用户选择
        cin >> select;

        if(select == 1)//添加账号
        {
            //cout << "add" << endl;
            man->addPerson();
        }
        else if(select == 2)//查看账号
        {
            //cout << "show1" << endl;
            man->showPerson();
        }
        else if(select == 3)//查看机房
        {
            //cout << "show2" << endl;
            man->showComputer();
        }
        else if(select == 4)//清空预约
        {
            //cout << "clear" << endl;
            man->cleanFile();
        }
        else
        {
            delete &manager;//销毁堆区对象
            cout << "ESC" << endl;
            system("pause");
            system("cls");
            return;
        }
        
    }
}

//登录功能 参数一 操作文件名 参数二 操作身份类型
void LoginIn(string fileName, int type)
{
    //父类指针 指向子类对象
    Identity *person = NULL;
    //读文件
    ifstream ifs;
    ifs.open(fileName, ios::in);

    if(!ifs.is_open())
    {
        cout << "FILE IS NOT EXIST" << endl;
        ifs.close();
        return;
    }

    //接受用户信息
    int id = 0;
    string name;
    string pwd;

    //判断身份
    if(type == 1)  //学生
    {
        cout << "PRINT YOUR STUDENT ID" << endl;
        cin >> id;
    }
    else if(type == 2)  //老师
    {
        cout << "PRINT YOUR TEACHER ID" << endl;
        cin >> id;
    }

    cout << "PRINT YOUR USERNAME" << endl;
    cin >> name;

    cout << "PRINT YOUR PASSWORD" << endl;
    cin >> pwd;

    if(type == 1)
    {
        //学生身份验证
        int fId;//文件中id
        string fName;//文件中的name
        string fPwd;//文件中密码
        while(ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            //与用户信息对比
            if(fId == id && fName == name && fPwd == pwd)
            {
                cout << "STUDENT SUCCESS LOGIN IN" << endl;
                system("pause");
                system("cls");
                person = new Student(id,name,pwd);

                //进入学生子页面
                studentMenu(person);
                return;
            }
        }
    }
    else if(type == 2)
    {
        //老师身份验证
        int fId;//文件中id
        string fName;//文件中的name
        string fPwd;//文件中密码
        while(ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            //与用户信息对比
            if(fId == id && fName == name && fPwd == pwd)
            {
                cout << "TEACHER SUCCESS LOGIN IN" << endl;
                system("pause");
                system("cls");
                person = new Teacher(id,name,pwd);

                //进入老师子页面
                teacherMenu(person);
                return;
            }
        }
    }
    else if(type == 3)
    {
        //管理员身份验证
        string fName;//文件中的name
        string fPwd;//文件中密码
        while(ifs >> fName && ifs >> fPwd)
        {
            //与用户信息对比
            if(fName == name && fPwd == pwd)
            {
                cout << "ADMIN SUCCESS LOGIN IN" << endl;
                system("pause");
                system("cls");
                person = new Manager(name,pwd);

                //进入管理员子页面
                managerMeun(person);

                return;
            }
        }
    }


    cout << "FAILED TO CONTANT!" << endl;
    system("pause");
    system("cls");
}

int main() {

    int select = 0;//接受用户选择

    while(true)
    {
        cout << "==============WELCOME TO COMPUTER RESERVE SYSTEM==============" << endl;

        cout << "CHOOSE YOUR POSITION" << endl;
        cout << "\t\t-------------------------\n";
        cout << "\t\t|                        |\n";
        cout << "\t\t|      1.Student         |\n";
        cout << "\t\t|                        |\n";
        cout << "\t\t|      2.Teacher         |\n";
        cout << "\t\t|                        |\n";
        cout << "\t\t|      3.Admin           |\n";
        cout << "\t\t|                        |\n";
        cout << "\t\t|      0.Exit            |\n";
        cout << "\t\t|                        |\n";
        cout << "\t\t-------------------------\n";

        cout << "Please input your choice: ";

        cin >> select;//用户输入

        switch (select)//根据用户选项，实现不同接口
        {
        case 1://学生
            LoginIn(STUDENT_FILE,1);
            break;
        case 2://老师
            LoginIn(TEACHER_FILE,2);
            break;
        case 3://管理员
            LoginIn(ADMIN_FILE,3);
            break;
        case 0://退出
            cout << "Welcome to next use" << endl;
            system("pause");
            return 0;
            break;

        default:
            cout << "Input error, Please return again." << endl;
            system("pause");
            system("cls");
            break;
        }
    }

    

    system("pause");
    return 0;
}