#include "teacher.h"

//默认构造
Teacher::Teacher(){}

//有参构造
Teacher::Teacher(int empId, string name, string pwd)
{
    //初始化属性
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

//操作菜单  纯虚函数
void Teacher::openMeun()
{
    cout << "WELCOME TEACHER:" << this->m_Name << endl;
    cout << "\t\t-------------------------\n";
    cout << "\t\t|      1.Show All Order  |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      2.Valid Order     |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      0.Exit            |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t-------------------------\n";
}

//查看所有学生预约
void Teacher::showAllOeder()
{
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout << "No review!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    for(int i = 0; i < of.m_Size; i++)
    {
        cout << i + 1 << ",";
        cout << "Order date: " << of.m_orderData[i]["date"];
        cout << "  Order interval:" << (of.m_orderData[i]["interval"] == "1" ? "morning" : "afternoon");
        cout << "  Order stuId: " << of.m_orderData[i]["stuId"];
        cout << "  Order stuName: " << of.m_orderData[i]["stuName"];
        cout << "  Order roomId: " << of.m_orderData[i]["roomId"];

        string status = "  status: ";
        //1 审核中 2 已预约 -1 预约失败 0 取消预约
        if(of.m_orderData[i]["status"] == "1")
        {
            status += "Reviewing~~~";
        }
        else if(of.m_orderData[i]["status"] == "2")
        {
            status += "Review success.";
        }
        else if(of.m_orderData[i]["status"] == "-1")
        {
            status += "Review failed!!!";
        }
        else
        {
            status += "Review cancel";
        }
        cout << status << endl;
    }
    system("pause");
    system("cls");
}

//审核所有预约
void Teacher::validOrder()
{
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout << "No review record!!" << endl;
        system("pause");
        system("cls");

        return;
    }

    vector<int>v;
    int index = 0;
    cout << "Need review message:" << endl;

    for(int i = 0; i < of.m_Size; i++)
    {
        if(of.m_orderData[i]["status"] == "1")
        {
            v.push_back(i);
            cout << ++index << " ,";
            cout << "Order date: " << of.m_orderData[i]["date"];
            cout << "  Order interval:" << (of.m_orderData[i]["interval"] == "1" ? "morning" : "afternoon");
            cout << "  Order stuId: " << of.m_orderData[i]["stuId"];
            cout << "  Order stuName: " << of.m_orderData[i]["stuName"];
            cout << "  Order roomId: " << of.m_orderData[i]["roomId"];

            cout << " status: reviewing~~" << endl;
        }
    }

    cout << "Input valid order number, 0 = return" << endl;
        int select = 0;//接受用户选择的预约记录
        int ret = 0;//接受结果记录
        while(true)
        {
            cin >> select;
            if(select >=0 && select <= v.size())
            {
                if(select == 0)
                {
                    break;
                }
                else
                {
                    cout << "Input your valid result" << endl;
                    cout << "1. Pass" << endl;
                    cout << "2.Out" << endl;
                    cin >> ret;

                    if(ret == 1)
                    {
                        //通过
                        of.m_orderData[v[select - 1]]["status"] = "2";
                    }
                    else
                    {
                        //不通过
                        of.m_orderData[v[select - 1]]["status"] = "-1";
                    }

                    of.updateOrder();//更新记录
                    cout << "valid success" << endl;
                    break;
                }
                system("pause");
                system("cls");
            }
            
            cout << "Input error!" << endl;
        }
}