#include <bits/stdc++.h>

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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n = 5;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }

    auto work = [&](vector<int> &v, int l, int r) {
        int m = l + r >> 1;
        for (int i = l; i <= m; i++) {
            swap(v[i], v[r + l - i]);
        }
    };

    set<vector<int>> S;
    for (int i = 0; i < n; i++) {
        vector<int> v(n);
        for (int j = 0; j < n; j++) {
            v[j] = (i + j) % n;
        }
        S.insert(v);
    }

    for (int l1 = 0; l1 < n; l1++) {
        for (int r1 = l1; r1 < n; r1++) {
            vector<int> now = p;
            work(now, l1, r1);
            for (int l2 = 0; l2 < n; l2++) {
                for (int r2 = l2; r2 < n; r2++) {
                    work(now, l2, r2);
                    // if (S.count(now)) {
                    debug(now, l1, r1, l2, r2);
                    // }
                }
            }
        }
    }
}