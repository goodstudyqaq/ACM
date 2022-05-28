#include <bits/stdc++.h>

#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

void part_two_solution(string s) {
    int s_len = s.size();
    set<string> S;
    for (int i = 0; i + 2 <= s_len - 1; i++) {
        string tmp = s.substr(i, 3);
        S.insert(tmp);
    }
    cout << (int)S.size() << endl;
}

void part_three_solution(string s) {
    int depth = 1;
    int now = 0;
    int n = s.size();

    int need_depth = sqrt(1.0 * n);
    if (need_depth * need_depth < n) need_depth++;

    while (now < n) {
        int length = depth * 2 - 1;
        int go = min(n, now + length);
        int space_num = need_depth - depth;
        for (int i = 0; i < space_num; i++) {
            cout << ' ';
        }
        for (int i = now; i < go; i++) {
            cout << s[i];
        }
        cout << endl;
        now = go;
        depth++;
    }
}

int main() {
    string str = "asdfasdfasdfafafasdsdfsadfasdfgfafasdffasdfasdfafasasfedfafafasdfasd";
    set<char> counter;

    for (int i = 0; i < str.size(); i++) {
        counter.insert(str[i]);
    }
    cout << counter.size() << endl;

    part_two_solution("abcbcb");
    part_three_solution("asdfasdfasdfafafasdsdfsadfasdfgfafasdffasdfasdfafasasfedfafafasdfasd");

    return 0;
}