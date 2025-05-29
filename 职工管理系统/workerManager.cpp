#include "workerManager.h"

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

//初始化员工
void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int index = 0;

    while(ifs >> id && ifs >> name && ifs >> dId)
    {
        Worker * worker = NULL;

        if(dId == 1)//普通职工
        {
            worker = new Employee(id,name,dId);
        }
        else if(dId == 2)//经理
        {
            worker = new Manager(id,name,dId);
        }
        else//老板
        {
            worker = new Boss(id,name,dId);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }

    //关闭文件
    ifs.close();

}


WorkerManager::WorkerManager()
{
    //1.文件不存在
    ifstream ifs;
    ifs.open(FILENAME, ios::in); //读文件

    if( !ifs.is_open())
    {
        //cout << "file is not exist" << endl;
        //初始化属性
        //初始化记录人数
        this->m_EmpNum = 0;
        //初始化数组指针
        this-> m_EmpArray = NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true; 
        ifs.close();
        return;
    }

    //2.文件存在，内容为空
    char ch;
    ifs >> ch;
    if(ifs.eof())
    {
        //文件为空
        //cout << "file is empty" << endl;
        //初始化记录人数
        this->m_EmpNum = 0;
        //初始化数组指针
        this-> m_EmpArray = NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true; 
        ifs.close();
        return;
    }

    //3.文件存在，有数据
    int num = this->get_EmpNum();
    //cout << "worker number = " << num << endl;
    this->m_EmpNum = num;

    //开辟空间
    this->m_EmpArray = new Worker*[ this-> m_EmpNum];
    //将文件数据，存入数组中
    this->init_Emp();

    //测试代码
    // for(int i = 0; i < this->m_EmpNum; i++)
    // {
    //     cout << "  employee id:   " << this->m_EmpArray[i]->m_Id
    //          << "  name:   " << this->m_EmpArray[i]->m_name
    //          << "  department id:   " << this->m_EmpArray[i]->m_DeptId << endl;
    // }

}

//展示菜单
void WorkerManager::ShowMenu ()
{
    cout <<"************************************" << endl;
    cout <<"******* welcome to system **********" << endl;
    cout <<"********  0. exit ******************" << endl;
    cout <<"********  1. add employee  *********" << endl;
    cout <<"********  2. show employee  ********" << endl;
    cout <<"********  3. delete emplyee  *******" << endl;
    cout <<"********  4. alter employee  *******" << endl;
    cout <<"********  5.search employee  *******" << endl;
    cout <<"********  6.order by employee  *****" << endl;
    cout <<"********  7.drop message  **********" << endl;
    cout <<"************************************" << endl;
    cout << endl;
}

//退出
void WorkerManager::ExitSystem()
{
    cout <<"waiting for next time" << endl;
    system("pause");
    exit(0);//退出程序
}

//添加员工
void WorkerManager::AddEmp()
{
    cout << "please choose your add number" << endl;

    int addNum = 0;//记录用户输入数量
    cin >> addNum; 

    if(addNum > 0)
    {
        //添加
        //计算添加新空间大小
        int newSize = this->m_EmpNum + addNum;//新空间人数 = 原空间人数 + 添加人数

        //开辟新空间
        Worker ** newSpace = new Worker*[newSize]; 

        //将原来空间下数据拷贝到新空间下
        if(this->m_EmpArray != NULL)
        {
            for(int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //批量添加数据
        for(int i = 0; i < addNum; i++)
        {
            int id;//职工编号
            string name;//职工姓名
            int dSelect;//部门选择

            cout << "choose worker" << i + 1 << "id:" << endl;
            cin >> id;

            cout << "choose worker" << i + 1 << "name:" << endl;
            cin >> name;

            cout << "choose worker position" << endl;
            cout << "1.employee" << endl;
            cout << "2.manager" << endl;
            cout << "3.boss" << endl;
            cin >> dSelect;

            Worker * worker = NULL;
            switch(dSelect)
                {
                case 1:
                    worker = new Employee(id, name, 1);
                    break;
                case 2:
                    worker = new Manager(id, name, 2);
                    break;
                case 3 :
                    worker = new Boss(id, name, 3);
                    break;
                default:
                    break;
                }
                //将创建职工指针，保存到数组
                newSpace[this->m_EmpNum + i] = worker;
            }

        //释放原有空间
        delete[] this->m_EmpArray;

        //更改新空间指向
        this->m_EmpArray = newSpace;

        //更新新职工人数
        this->m_EmpNum = newSize;

        //添加数据成功，文件不为空，更新
        this->m_FileIsEmpty = false;

        //提示添加成功
        cout <<"success add" << addNum << "worker" << endl;

        //保存数据到文件
        this->save();
    }
    else
    {
        cout <<"error" << endl;
    }

    //按任意键后清屏回到上级目录
    system("pause");
    system("cls");

} 

//保存文件
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);//写文件

    //将数据写入文件中
    for(int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << "  "
            << this->m_EmpArray[i]->m_name << "  "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }

    //关闭文件
    ofs.close();
}

//统计文件中人数
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//读文件
    int id;
    string name;
    int dId;

    int num = 0;

    while(ifs >> id && ifs >> name && ifs >> dId)
    {
        //统计人数
        num++;
    }

    return num;
}

//显示职工
void WorkerManager::ShowEmp()
{
    //判断文件是否为空
    if(this->m_FileIsEmpty)
    {
        cout << "file not exist or file is empty, please add data" << endl;
    }
    else
    {
        for(int i = 0; i < m_EmpNum; i++)
        {
            //利用多态调用接口
            this->m_EmpArray[i]->showInfo();
        }
    }
    //按任意键清屏
    system("pause");
    system("cls");
}

//判断职工是否存在
int WorkerManager::IsExist(int id)
{
    int index = -1;
    for(int i = 0; i < this->m_EmpNum; i++)
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            //找到该编号职工
            index = i;

            break;
        }
    }
    return index;
}

//删除职工
void WorkerManager::DelEmp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "file is not exist" << endl;
    }
    else
    {
        //按照职工编号删除
        cout << "print delete id" << endl;
        int id = 0;
        cin >> id;
        int index = this->IsExist(id);
        if(index != -1)
        {
            //删除职工存在，可以下一步
            for(int i = index; i < this->m_EmpNum - 1; i++)
            {
                //数据前移
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            //维护删除后人数
            this->m_EmpNum--;
            //同步更新文件
            this->save();

            cout <<"delete success" << endl;

        }
        else
        {
            cout << "NOT FOUND FAILED" << endl;
        }
    }

    //按任意键清屏
    system("pause");
    system("cls");
}

//修改职工
void WorkerManager::ModEmp()
{
    if(this->m_FileIsEmpty)
    {
        cout <<"FILE IS EMPTY" << endl;
    }
    else
    {
        cout << "print modify employee id" << endl;
        int id;
        cin >> id;

        int ret = this->IsExist(id);
        if(ret != -1)
        {
            //查到员工，开始操作

            delete this->m_EmpArray[ret];

            int newId = 0;
            string newName = "";
            int dSelect = 0;

            cout << "FIND" << id << "EMPLOYEE" << endl;

            cout << "PLEASE WRITE NEW ID" << endl;
            cin >> newId;
            cout << "PLEASE WRITE NEW NAME" << endl;
            cin >> newName;
            cout << "PLEASE WRITE NEW POSITION" << endl;
            cout << "1.employee" << endl;
            cout << "2.manager" << endl;
            cout << "3.boss" << endl;
            cin >> dSelect;
            Worker * worker = NULL;
            switch(dSelect)
                {
                case 1:
                    worker = new Employee(newId, newName, dSelect);
                    break;
                case 2:
                    worker = new Manager(newId, newName, dSelect);
                    break;
                case 3 :
                    worker = new Boss(newId, newName, dSelect);
                    break;
                default:
                    break;
                }

                //更新数据到数组
                this->m_EmpArray[ret] = worker;

                cout << "MODIFY SUCCESS" << endl;

                //保存到文件
                this->save();
        }
        else
        {
            cout << "NOT FOUND EMPLOYEE" << endl;
        }
    }

    //按任意键清屏
    system("pause");
    system("cls");

}

//查找职工
void WorkerManager::FindEmp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "FILE IS EMPTY" << endl;
    }
    else
    {
        cout << "SELECT SEARCHING WAY" << endl;
        cout << "1.BY FROM EMPLAYMENT_ID" << endl;
        cout << "2.BY FROM NAME" << endl;
        int select = 0;
        cin >> select;

        if(select == 1)
        {
            //1.按照id查
            int id;
            cout << "CHOOSE SEARCHING ID" << endl;
            cin >> id;

            int ret = IsExist(id);
            if(ret != -1)
            {
                //找到员工
                cout <<"FIND SUCCESS" << endl;
                cout << "MESSAGE:" << endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout << "FAILED FIND" << endl;
            }
        }
        else if(select == 2)
        {
            //2.按照姓名查
            string name;
            cout << "CHOOSE SEARCHING NAME" << endl;
            cin >> name;

            //加入判断查找是否查到标志
            bool flag =false;//默认没有

            for(int i = 0; i < m_EmpNum; i++)
            {
                if(this->m_EmpArray[i]->m_name == name)
                {
                    cout << "FIND SUCCESS MESSAGE:" << endl;

                    flag = true;

                    //调用信息
                    this->m_EmpArray[i]->showInfo();
                }
            }
            if(flag == false)
            {
                cout << "NOT FOUND" << endl;
            }
        }
        else
        {
            cout << "ERROR" << endl;
        }
    }
    //按任意键清屏
    system("pause");
    system("cls");
}

//排序
void WorkerManager::SortEmp()
{
    if(this->m_FileIsEmpty)
    {
    //按任意键清屏
    system("pause");
    system("cls");
    }
    else
    {
        cout << "SELECT YOUR CHOICE" << endl;
        cout << "1.AS ORDER" << endl;
        cout << "2.DESC ORDER" << endl;
        int select = 0;
        cin >> select;

        for(int i = 0; i < m_EmpNum; i++)
        {
            int minormax = i;//最小最大下标
            for(int j = i + 1; j < m_EmpNum; j++)
            {
                if(select == 1)//升序
                {
                    if(m_EmpArray[minormax]->m_Id > m_EmpArray[j]->m_Id)
                    {
                        minormax = j;
                    }
                }
                else //降序
                {
                    if(m_EmpArray[minormax]->m_Id < m_EmpArray[j]->m_Id)
                    {
                        minormax = j;

                    }
                }
                
            }

            //交换数据
            if(i != minormax)
            {
                Worker * temp = m_EmpArray[i];
                m_EmpArray[i] = m_EmpArray[minormax];
                m_EmpArray[minormax] = temp;
            }

        }

        cout <<"SORT SUCCESS MESSAGE:" << endl;
        this->save();//排序后结果保存，同步更新
        this->ShowEmp();//展示所有职工
    }
}

//清空文件
void WorkerManager::CleanFile()
{
    cout << "ARE YOU SURE TO CLEAN" << endl;
    cout <<"1.YES" << endl;
    cout <<"2.NO" << endl;
    int select = 0;
    cin >> select;

    if(select == 1)
    {
        //确定删除，清空文件
        ofstream ofs(FILENAME, ios::trunc); //删除后重新创建
        ofs.close();

        if(this->m_EmpArray != NULL)
        {
            //删除堆区每个对象
            for(int i = 0; i < this->m_EmpNum; i++)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
            //删除堆区数组指针
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        
        cout << "CLEANING SUCCESS" << endl;
    }

    //按任意键清屏
    system("pause");
    system("cls");
}

WorkerManager::~WorkerManager()
{
    if(this->m_EmpArray != NULL)
    {
        for(int i = 0; i < this->m_EmpNum; i++)
        {
            if(this->m_EmpArray[i] != NULL)
            {
                delete this->m_EmpArray[i];
            }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }

}