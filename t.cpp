#include <iostream>
#include <bitset>
using namespace std;

// 打印一个整数的二进制表示
void print_binary(int num) {
    // 假设输出为32位二进制
    for (int i = 31; i >= 0; --i) {
        // 使用按位与操作获取每一位，右移后打印
        cout << ((num >> i) & 1);
    }
    cout << endl;
}

int main() {
   int a=2;
   int b=~a;
   int c=a&b;
   int d=~a+2;
   cout<<a<<endl;
   cout<<b<<endl;
   cout<<c<<endl;
   cout<<d<<endl;
    return 0;
}
