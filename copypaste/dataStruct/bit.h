#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct Fenwick {
#define lowbit(x) x & -x
    const int n;
    vector<T> a;
    Fenwick(int n) : n(n), a(n + 1) {}
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    T query(int x) {
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }
};