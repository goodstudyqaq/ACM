#include <bits/stdc++.h>

#include "./structure/others/linear-sparse-table.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

namespace GenHelper {
unsigned z1, z2, z3, z4, b;
unsigned rand_() {
    b = ((z1 << 6) ^ z1) >> 13;
    z1 = ((z1 & 4294967294U) << 18) ^ b;
    b = ((z2 << 2) ^ z2) >> 27;
    z2 = ((z2 & 4294967288U) << 2) ^ b;
    b = ((z3 << 13) ^ z3) >> 21;
    z3 = ((z3 & 4294967280U) << 7) ^ b;
    b = ((z4 << 3) ^ z4) >> 12;
    z4 = ((z4 & 4294967168U) << 13) ^ b;
    return (z1 ^ z2 ^ z3 ^ z4);
}
}  // namespace GenHelper
void srand(unsigned x) {
    using namespace GenHelper;
    z1 = x;
    z2 = (~x) ^ 0x233333333U;
    z3 = x ^ 0x1234598766U;
    z4 = (~x) + 51;
}
int read() {
    using namespace GenHelper;
    int a = rand_() & 32767;
    int b = rand_() & 32767;
    return a * 32768 + b;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m, s;
    cin >> n >> m >> s;
    srand(s);
    vector<int> V(n);
    for (int i = 0; i < n; i++) {
        V[i] = read();
    }
    using F = function<int(int, int)>;
    LinearSparseTable<int, F> lst(V, [&](int x, int y) {
        return x > y ? x : y;
    });

    unsigned long long ans = 0;
    while (m--) {
        int l = read() % n + 1, r = read() % n + 1;
        if (l > r) swap(l, r);
        l--;
        r--;
        int res = lst.fold(l, r + 1);
        ans += res;
    }
    cout << ans << endl;
}