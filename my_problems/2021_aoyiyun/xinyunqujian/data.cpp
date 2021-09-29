#include <bits/stdc++.h>

using namespace std;

// 验证正确性
// 随机 1 到 4 的数
// data1 ~ data3
void work1() {
    int n = 100000;
    cout << n << endl;

    for (int i = 1; i <= n; i++) {
        int val = rand() % 4 + 1;
        cout << val << ' ';
    }
    cout << endl;
}

// 验证是否乘超 long long
// data4 ~ data5
void work2() {
    int n = 100000;
    cout << n << endl;

    for (int i = 1; i <= n; i++) {
        int val = rand() % 1000000000 + 1;
        cout << val << ' ';
    }
    cout << endl;
}

// 混合
// data6 ~ data9
void work3() {
    int n = 100000;
    cout << n << endl;

    for (int i = 1; i <= n; i++) {
        bool f = rand() % 2;
        if (f) {
            int val = rand() % 4 + 1;
            cout << val << ' ';
        } else {
            int val = rand() % 1000000000 + 1;
            cout << val << ' ';
        }
    }
    cout << endl;
}

// 特殊case 所有都是 1
// data10
void work4() {
    int n = 100000;
    cout << n << endl;
    for (int i = 1; i <= n; i++) {
        cout << 1 << ' ';
    }
    cout << endl;
}

int main() {
    srand((unsigned int)time(NULL));
    string OUT = "data10.in";
    freopen(OUT.c_str(), "w", stdout);
    work4();
}