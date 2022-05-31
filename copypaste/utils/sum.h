#include <bits/stdc++.h>
using namespace std;

using ll = long long;
struct Sum {
    // sum1 前缀和 sum2 前缀和的前缀和
    vector<ll> sum1, sum2;
    // 从 1 开始
    Sum(vector<int> &a) {
        int n = a.size() - 1;
        sum1.resize(n + 1);
        sum2.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            sum1[i] = sum1[i - 1] + a[i];
            sum2[i] = sum2[i - 1] + sum1[i];
        }
    }

    // 计算 (i, r] 所有点到 i + 1 的区间和的和
    ll get_special_sum1(int i, int r) {
        return (sum2[r] - sum2[i]) - sum1[i] * (r - i);
        // 如果想计算 [i, r] 到 i 的区间和，只需要加上 (r - i) * a[i] 即可
    }

    // 以 i 为起点，计算 [l, i] 所有点到 i 的区间和的和
    ll get_special_sum2(int i, int l) {
        return sum1[i] * (i - l + 1) - (sum2[i] - sum2[l - 1]) + sum1[i] - sum1[l - 1];
    }
};
