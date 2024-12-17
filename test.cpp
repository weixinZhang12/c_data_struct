#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
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
    }
    // 打印信息，无序打印
    void print_info()
    {
        unsigned int lines = 1;
        cout << "-------------------------------------\n";
        // 输出字段部分
        cout << left << setw(12) << "NAME"
             << "|" << setw(12) << "ID"
             << "|" << setw(5) << "AGE"
             << "|" << setw(5) << "GRADE"
             << "\n";
        cout << "-------------------------------------\n";
        // 输出学生的信息部分
        for (const auto &entry : map)
        {
            if (!is_even(lines))
            {
                cout << "\e[7m" << left << setw(12) << entry.second->name
                     << "|" << setw(12) << entry.second->id
                     << "|" << setw(5) << entry.second->age
                     << "|" << setw(5) << entry.second->grade
                     << "\e[0m\n";
                lines += 1;
                continue;
            }

            cout << left << setw(12) << entry.second->name
                 << "|" << setw(12) << entry.second->id
                 << "|" << setw(5) << entry.second->age
                 << "|" << setw(5) << entry.second->grade
                 << "\n";
            lines += 1;
        }
        cout << "-------------------------------------\n";
    }
    // 从csv文件中添加学生信息
    void add_student_info_from_csv()
    {
        // 临时存储结结果
        vector<string> result;
        // 打开文件
        ifstream file("./t.csv");
        if (!file.is_open())
        {
            cerr << "文件无法正常打开" << endl;
            return;
        }
        int t = 0;
        string line;
        unsigned int lines = 1;

        // 读取字符串
        while (getline(file, line))
        {
            // 此时并非最优性能
            vector<string> temp;
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
                break;
            }
            // for (const auto &entry : temp)
            // {
            //     cout << entry << endl;
            // }
            try
            {
                Student *student = new Student(temp[0], stol(temp[1]), stoi(temp[2]), stol(temp[3]));
                map.insert({stol(temp[1]), student});
                temp.clear();
                lines += 1;
            }
            // 数据类型错误
            catch (const invalid_argument &e)
            {
                cerr << "\e[1;31m"<<lines<<"行含有无效的数据\e[0m" << endl;
                ;
                continue;
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    StudentManger *manger = new StudentManger;
    manger->add_student_info_from_csv();
    manger->print_info();
    return 0;
}
