#include "student.h"
//默认构造
Student::Student()
{

}

//有参构造
Student::Student(int id, string name, string pwd)
{
    //初始化
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;
    
    //初始化机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE,ios::in);

    ComputerRoom com;
    while(ifs >> com.m_ComId && ifs >> com.m_MaxNum)
    {
        //将读取信息放入容器
        vCom.push_back(com);
    }

    ifs.close();
}

//菜单界面
void Student::openMeun()
{
    cout << "WELCOME STUDENT:" << this->m_Name << endl;
    cout << "\t\t-------------------------\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      1.Apply Order     |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      2.Show My Order   |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      3.Show All Order  |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      4.Cancel Order    |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t|      0.Exit            |\n";
    cout << "\t\t|                        |\n";
    cout << "\t\t-------------------------\n";
}

//申请预约
void Student::applyOrder()
{
    cout << "Computer room open time: monday~friday!" << endl;
    cout << "Input your order time:" << endl;
    cout << "1. Monday" << endl;
    cout << "2. Tusday" << endl;
    cout << "3. Wedsday" << endl;
    cout << "4. Thursday" << endl;
    cout << "5. Friday" << endl;

    int date = 0;  // 日期
    int interval = 0; //时间段
    int room = 0; //机房号

    while (true)
    {
        cin >> date;
        if(date >= 1 && date <= 5)
        {
            break;
        }
        cout << "Date Error!!!" << endl;
    }

    cout << "Input your order interval:" << endl;
    cout << "1 Morning" << endl;
    cout << "2 Afternoon" << endl;

    while (true)
    {
        cin >> interval;
        if(interval >= 1 && interval <= 2)
        {
            break;
        }
        cout << "Interval Error!!!" << endl;
    }

    cout << "Input your order computer room:" << endl;
    for(int i = 0; i < vCom.size(); i++)
    {
        cout << "Number:" <<vCom[i].m_ComId << " Empty seat:" << vCom[i].m_MaxNum << endl;
    }
    
    while (true)
    {
        cin >> room;
        if(room >= 1 && room <= 3)
        {
            break;
        }
        cout << "Room Error!!!" << endl;
    }

    cout << "Apply Success! Checking" << endl;

    ofstream ofs;
    ofs.open(ORDER_FILE,ios::app);

    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << endl;

    ofs.close();
    system("pause");
    system("cls");

}

//查看自身预约
void Student::showMyOrder()
{
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout << "No order record!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    for(int i = 0; i < of.m_Size; i++)
    {
        //string转int
        //string 利用 .c_str() 转 const char*
        //利用 atoi (const char *) 转int
        if(this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
        {
            //找到自身预约
            cout << "Order date: " << of.m_orderData[i]["date"];
            cout << "  Order interval:" << (of.m_orderData[i]["interval"] == "1" ? "morning" : "afternoon");
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
    }
    system("pause");
    system("cls");
}

//查看所有预约
void Student::showAllOrder()
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

//取消预约
void Student::cancelOrder()
{
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout << "No review" << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "Reviewing and Review success can be cancel" << endl;
    
    vector<int>v; //存放在最大容器中的下标编号
    int index = 1;
    for(int i = 0; i < of.m_Size; i++)
    {
        //先判断是自己
        if(this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
        {
            //筛选状态 审核中1 预约成功 2
            if(of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                v.push_back(i);
                cout << index++ << ",";
                cout << "Order date: " << of.m_orderData[i]["date"];
                cout << "  Order interval:" << (of.m_orderData[i]["interval"] == "1" ? "morning" : "afternoon");
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
                cout << status << endl;
            }
        }
    }

    cout << "Input your cancel review 0 = return" << endl;

    int select = 0;
    while(true)
    {
        cin >> select;

        if(select >= 0 && select <= v.size())
        {
            if(select == 0)
            {
                break;
            }
            else
            {
                of.m_orderData[ v[select - 1] ]["status"] = "0";

                of.updateOrder();

                cout << "Cancel success" << endl;
                break;
            }

        }

        cout << "Input error" << endl;
    }
    system("pause");
    system("cls");
}
