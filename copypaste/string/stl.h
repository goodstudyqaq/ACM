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

vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

/*
%02d 2位数字，不满补 0
*/
template <typename... Args>
std::string string_format(const std::string& format, Args... args) {
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;  // Extra space for '\0'
    if (size_s <= 0) {
        throw std::runtime_error("Error during formatting.");
    }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1);  // We don't want the '\0' inside
}

}  // namespace STL