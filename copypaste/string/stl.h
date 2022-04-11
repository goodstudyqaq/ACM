#include <bits/stdc++.h>
using namespace std;
namespace STL {
/*
记录一些常用的 STL 函数
*/
void StringSTL() {
    string s = "123";
    int num = stoi(s);  // string to int 返回字符串前缀整数，可以有前导零，前缀必须是数字(第一个字符可以是 ‘-’)
    s = "247+38";
    int add = s.find('+', 0);  // 从 pos 开始查找，返回第一个匹配的下标
}

}  // namespace STL