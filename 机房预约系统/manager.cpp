#include "manager.h"

//默认构造
Manager::Manager()
{
    
}

//有参构造
Manager::Manager(string name, string pwd)
{
    //初始化管理员信息
    this->m_Name = name;
    this->m_Pwd = pwd;

    //初始化容器，获取容器中学生老师信息
    this->initVector();

    //初始化机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE,ios::in);

    ComputerRoom com;
    while(ifs >> com.m_ComId && ifs >> com.m_MaxNum)
    {
        vCom.push_back(com);
    }
    ifs.close();
    cout << "Computer room number:" << vCom.size() << endl;
}

//菜单界面
void Manager::openMeun()
{
    cout << "WELCOME MANAGER:" << this->m_Name << endl;
    cout << "\t\t-------------------------\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      1.Add Person      |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      2.Show Person     |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      3.Show Computer   |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      4.Clean File      |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      0.Exit            |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t-------------------------\n";
}

//添加账号
void Manager::addPerson()
{
    cout << "Print Your Type" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Add Teacher" << endl;

    string fileName;//需要操作的文件名
    string tip; //提示id号
    string errorTip;//重复错误提示

    ofstream ofs;//文件操作对象

    int select = 0;
    cin >> select;

    if(select == 1)
    {
        //添加的为学生
        fileName = STUDENT_FILE;
        tip = "Print Your Student Id:";
        errorTip = "Student_id ERROR:" ;
    }
    else
    {
        fileName = TEACHER_FILE;
        tip = "Print Your Teacher Id:";
        errorTip = "Teacher_id ERROR" ;
    }

    ofs.open(fileName,ios::out | ios::app);//利用追加方式写文件

    int id;//学号/职工号
    string name;//姓名
    string pwd;//密码

    cout << tip << endl;
    
    while(true)
    {
        cin >> id;
        bool ret = checkRepeat(id,select);
        if(ret)//有重复
        {
            cout << errorTip << endl;
        }
        else
        {
            break;
        }
    }

    cout << "Print Your Name:" << endl;
    cin >> name;

    cout << "Print Your Password:" << endl;
    cin >> pwd;

    //向文件中添加数据
    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "Success" << endl;

    system("pause");
    system("cls");

    ofs.close();

    //调用初始化接口，更新数据
    this->initVector();
}

void printStudent(Student &s)
{
    cout << "Id = " << s.m_Id << " Name = " << s.m_Name << endl;
}

void printTeacher(Teacher &t)
{
    cout << "EmpId = " << t.m_EmpId<< " Name = " << t.m_Name << endl;
}

//查看账号
void Manager::showPerson()
{
    cout << "CHOOOSE TYPE:" << endl;
    cout << "1 Studnet Content" << endl;
    cout << "2 Teacher Content" << endl;

    int select = 0;//接受用户选择
    cin >> select;

    if(select == 1) //查看学生
    {
        cout << "ALL STUDENT MESSAGE:" << endl;
        for_each(vStu.begin(),vStu.end(),printStudent);
    }
    else //查看老师
    {
        cout << "ALL TEACHER MESSAGE:" << endl;
        for_each(vTea.begin(),vTea.end(),printTeacher);
    }

    system("pause");
    system("cls");
}

//查看机房信息
void Manager::showComputer()
{
    cout << "ALL COMPUTER ROOM MESSAGE:" << endl;

    for(vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
    {
        cout << "Room Id = " << it->m_ComId << " Limit = " << it->m_MaxNum << endl;
    }

    system("pause");
    system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "CLEAR SUCCESS" << endl;
    system("pause");
    system("cls");
}

//初始化容器
void Manager::initVector()
{
    vStu.clear();//清空
    vTea.clear();//清空
    //读取信息 学生。老师
    ifstream ifs;
    ifs.open(STUDENT_FILE,ios::in);
    if(!ifs.is_open())
    {
        cout << "Loading Fail!" << endl;
        return;
    }
    Student s;
    while(ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
    {
        vStu.push_back(s);
    }

    cout << "Student number:" << vStu.size() << endl;
    ifs.close();

    //读取信息 老师

    ifs.open(TEACHER_FILE,ios::in);

    Teacher t;
    while(ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
    {
        vTea.push_back(t);
    }
    cout << "Teacher number:" << vTea.size() << endl;
    ifs.close();
}


//检测重复 参数一 id号 参数二 检测类型
bool Manager::checkRepeat(int id, int type)
{
    if(type == 1)//检测学生
    {
        for(vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
        {
            if(id == it->m_Id)
            {
                return true;
            }
        }
    }
    else //老师
    {
        for(vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
        {
            if(id == it->m_EmpId)
            {
                return true;
            }
        }
    }
    return false;
}