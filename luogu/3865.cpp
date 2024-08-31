#include <bits/stdc++.h>

#include "./structure/others/linear-sparse-table.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    vector<int> V(n);
    for (int i = 0; i < n; i++) {
        // cin >> V[i];
        V[i] = read();
    }
    using F = function<int(int, int)>;
    LinearSparseTable<int, F> lst(V, [&](int x, int y) {
        return x > y ? x : y;
    });

    while (m--) {
        int l = read();
        int r = read();
        l--, r--;
        cout << lst.fold(l, r + 1) << endl;
    }
    return 0;
}