#include <bits/stdc++.h>
using namespace std;

/*
https://atcoder.jp/contests/abc249/tasks/abc249_g
将 v 数组的 01 矩阵变为 step matrix, step matrix: 为对于每一行第一个非 0 列是单调递增的
转换完之后可以 On 求出任意选数，使得异或和最大
*/
vector<long long> convert(vector<long long> v, int bit) {
    int rk = 0;
    int n = v.size();
    vector<long long> res(n);
    for (int i = bit - 1; i >= 0; i--) {
        int go = rk;
        while (go < n && ((v[go] >> i) & 1) == 0) {
            go++;
        }
        if (go == n) continue;
        res[rk] = v[go];
        swap(v[rk], v[go]);
        for (int j = rk + 1; j < n; j++) {
            if ((v[j] >> i) & 1) {
                v[j] = v[j] ^ v[rk];
            }
        }
        rk++;
    }
    res.resize(rk);
    return res;
}