#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

// 正常输出信息,使用原始字符串
const string PRINT_INFO = R"(
--------------------------------
欢迎进入学生信息管理系统
--------------------------------
系统支以下功能:
    1.添加学生信息
    2.删除学生信息
    3.修改学生信息
    4.查询学生信息
    5.输出所有学生信息
    6.导出信息到csv文件 
    7.从本目录temp.csv导入数据
    8.语句模式（实验功能，暂时废弃）
--------------------------------
    0.退出系统
--------------------------------
你也可以使用命令行工具
help    提示帮助信息
)";
// 命令行工具输出信息
const string TERMUNAL_HELP_INFO = R"(
---------------------------------
欢迎使用命令行工具
---------------------------------
help               提示有关帮助信息
import <文件路径>   导入学生信息,支持csv文件
---------------------------------

)";
// 学生类
class Student
{
public:
    string name;
    long id;
    int age;
    int grade;
    Student(string name, long id, int age, int grade);
};
Student::Student(string name, long id, int age, int grade)
{
    this->name = name;
    this->id = id;
    this->age = age;
    this->grade = grade;
}
// 学生管理了类
class StudentManger
{
public:
    unordered_map<long, Student *> map;
    unsigned int length;
    StudentManger()
    {
        // printf("1");
    }
    // 判断这个数是否是偶数,用于高亮某些行
    bool is_even(int num)
    {
        return (num & 1) == 0;
    }
    // 添加学生信息
    void add_student(string name, long id, int age, int grade)
    {
        Student *s = new Student(name, id, age, grade);
        map.insert({s->id, s});
        length += 1;
    }
    void add_stundet_from_termial()
    {
        string name;
        long id;
        int age;
        int grade;
        cout << "请输入姓名：" << endl;
        cin >> name;
        cout << "请输入学生号" << endl;
        cin >> id;
        cout << "请输入年龄" << endl;
        cin >> age;
        cout << "请输入成绩" << endl;
        cin >> grade;
        this->add_student(name, id, age, grade);
    }
    void delete_student_info_by_id(long id, unordered_map<long, Student *> map)
    {
        auto it = map.find(id);
        // 如果没有找到元素返回map.end()
        if (it != map.end())
        {
            delete it->second;
            map.erase(id);
        }
    }
    void delete_student_info()
    {
        long id;
        cout << "请输入需要删除的学生的id" << endl;
        cin >> id;
        delete_student_info_by_id(id, map);
    }

    // 从csv文件中添加学生信息,该操作不会覆盖信息
    void add_student_info_from_csv(string path)
    {
        // 临时存储结结果
        vector<string> result;
        // 打开文件
        ifstream file(path);
        if (!file.is_open())
        {
            cerr << "\e[1;31m文件无法正常打开\e[0m" << endl;
            return;
        }
        int t = 0;
        // 用于存储行的内容
        string line;
        // 用于记录当前是哪一行
        unsigned int lines = 1;

        // 读取字符串
        while (getline(file, line))
        {
            // 此时并非最优性能
            vector<string> temp;
            // 声明一个需要切割的字符串
            stringstream ss(line);
            string s;
            // 分割字符串
            while (getline(ss, s, ','))
            {
                temp.push_back(s);
            }
            // 如果发现不满足条件的行,直接退出本次循环,跳过该行
            if (temp.size() != 4)
            {
                cerr << "\e[1;31m" << lines << "行出现问题\e[0m" << endl;
                // temp.clear();
                // lines+=1;
                continue;
                ;
            }
            try
            {
                this->add_student(temp[0], stol(temp[1]), stoi(temp[2]), stol(temp[3]));
                temp.clear();
                lines += 1;
            }
            // 数据类型错误
            catch (const invalid_argument &e)
            {
                cerr << "\e[1;31m" << lines << "行含有无效的数据\e[0m\n"
                     << e.what() << endl;
                continue;
            }
        }
        cout << "\e[1;32m导入完成\e[0m" << endl;
        // this->save_student_info_to_csv("temp.csv");
    }
    // 将数据导出到文件
    void export_studnet_info()
    {
        this->save_student_info_to_csv("./temp.csv");
    }
    // 将学生信息保存到csv文件
    void save_student_info_to_csv(string path)
    {
        ofstream file(path, ios::trunc);
        if (!file.is_open())
        {
            cerr << "\e[1,31m无法打开文件\e[0m" << endl;
        }
        for (const auto &entry : map)
        {
            file << entry.second->name << "," << entry.second->id << "," << entry.second->age << "," << entry.second->grade << endl;
        }
        file.close();
        cout << "\e[1;32m写入文件成功\e[0m" << endl;
    }
    // id升序比较函数
    static bool compare_by_id_raise(const Student *a, const Student *b)
    {
        return a->id < b->id;
    }
    static bool compare_by_grade_down(const Student *a, const Student *b)
    {
        return a->grade > b->grade;
    }
    // 按照id顺序升序打印
    void print_student_info_by_id()
    {
        vector<Student *> temp_v;
        for (const auto &entry : map)
        {
            temp_v.push_back(entry.second);
        }
        sort(temp_v.begin(), temp_v.end(), compare_by_id_raise);
        print_student_info(temp_v);
    }
    void print_student_info_by_grade()
    {
        vector<Student *> temp_v;
        for (const auto &entry : map)
        {
            temp_v.push_back(entry.second);
        }
        sort(temp_v.begin(), temp_v.end(), compare_by_grade_down);
        print_student_info(temp_v);
    }
    
    // 通用打印函数
    void print_student_info(const vector<Student *> vec)
    {

        unsigned int lines = 1;
        unsigned int index = 1;
        cout << "---------------------------------------------\n";
        // 输出字段部分
        cout << left << setw(7) << "INDEX"
             << "|" << setw(12) << "NAME"
             << "|" << setw(12) << "ID"
             << "|" << setw(5) << "AGE"
             << "|" << setw(5) << "GRADE"
             << "\n";
        cout << "---------------------------------------------\n";
        // 输出学生的信息部分
        for (const auto &entry : vec)
        {
            // 如果是奇数,高亮该行
            if (!is_even(lines))
            {
                cout << "\e[7m" << left << setw(7) << index
                     << "|" << setw(12) << entry->name
                     << "|" << setw(12) << entry->id
                     << "|" << setw(5) << entry->age
                     << "|" << setw(5) << entry->grade
                     << "\e[0m\n";
                lines += 1;
                index += 1;
                continue;
            }

            cout << left << setw(7) << index
                 << "|" << setw(12) << entry->name
                 << "|" << setw(12) << entry->id
                 << "|" << setw(5) << entry->age
                 << "|" << setw(5) << entry->grade
                 << "\n";
            index += 1;
            lines += 1;
        }
        cout << "---------------------------------------------\n";
    }
    // 打印信息，无序打印
    void print_info()
    {
        vector<Student *> temp_vec;
        for (const auto &entry : this->map)
        {
            temp_vec.push_back(entry.second);
        }
        print_student_info(temp_vec);
    }
    // 释放StudentManger的相关的内存
    ~StudentManger()
    {
        for (auto &entry : map)
        {
            delete entry.second;
        }
    }
};
// 处理命令行参数,使用完毕后程序退出
void argc_deal(int argc, char const *argv[], StudentManger *manger)
{
    // 当参数小于2时,不使用
    if (argc < 2)
    {
        return;
    }
    string commond = argv[1];
    // 导入文件
    if (commond == "import")
    {
        if (argv[2] == nullptr)
        {
            cerr << "\e[1;31m缺少第二个参数\e[0m" << endl;
            exit(1);
        }

        manger->add_student_info_from_csv(argv[2]);
    }
    // 导出文件
    if (commond == "export")
    {
        if (argv[2] == nullptr)
        {
            cerr << "\e[1;31m缺少第二个参数\e[0m" << endl;
            exit(1);
        }

        manger->save_student_info_to_csv(argv[2]);
    }
    // 帮助命令
    if (commond == "help")
    {
        cout << TERMUNAL_HELP_INFO << endl;
    }
    exit(0);
}
// 词法分析函数，用于分析语句
void command_parse()
{
    // 放置用户输入后的被拆分的文本
    vector<string> command_list;
    string user_input_string;
    // 这个方法不适用于读取整行的数据，cin遇到空格就会停止
    // cin >> user_input_string;
    cin.ignore();

    getline(cin, user_input_string);
    stringstream ss(user_input_string);
    string s;
    while (getline(ss, s, ' '))
    {
        command_list.push_back(s);
    }
    for (const auto &entry : command_list)
    {
        cout << entry << endl;
    }
}

void exit_application(bool &flag)
{
    string input;
    cout << "\e[33m请记得保存数据,再次点击回车确认，取消请点击任意字符\e[0m" << endl;
    getline(cin, input);
    if (input.empty())
    {
        flag = false;
    }
    else
    {
        cout << "\e[33m您已经取消退出\e[0m" << endl;
    }
}
int main(int argc, char const *argv[])
{

    StudentManger *manger = new StudentManger;
    argc_deal(argc, argv, manger);
    cout << "\e[32m" << PRINT_INFO << "\e[0m" << endl;
    // 如果用户没有使用命令行参数,下面命令将被执行
    // manger->add_student_info_from_csv("./temp.csv");
    // manger->print_info();
    int input;
    bool running = true;
    while (running)
    {
        cout << "请输入代码:";
        cin >> input;
        // 检查输入是否有效
        if (cin.fail())
        {
            cin.clear();                                         // 清除错误状态
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清理缓冲区
            cout << "\e[1;31m输入无效，请重新输入!\e[0m" << endl;
            continue; // 继续循环
        }
        // 清理掉缓冲区中的换行符，否则getline将直接读取换行符结束执行
        switch (input)
        {
        case 1:
            manger->add_stundet_from_termial();
            break;
        case 2:
            manger->delete_student_info();
            break;
        case 5:
            manger->print_student_info_by_grade();

            break;
        case 6:
            manger->export_studnet_info();
            break;
        case 7:
            manger->add_student_info_from_csv("./temp.csv");
            break;
        case 8:
            command_parse();
            manger->print_student_info_by_id();
            break;
        case 0:
            // running = false;
            exit_application(running);
            break;
        default:
            cout << "\e[32m" << PRINT_INFO << "\e[0m" << endl;
            break;
        }
    }

    return 0;
}
