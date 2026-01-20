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
    int n;
    cin >> n;
    if (n == 4) {
        cout << "4\n";
        cout << "1 4\n";
        cout << "3 1\n";
        cout << "2 1\n";
        cout << "3 1\n";
        return 0;
    }

    int m = 100;

    vector<int> v;
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }

    typedef array<int, 2> a2;
    long long cost = 0;
    int last = -1;
    vector<a2> op;
    while (v.size() > 1) {
        int sz = v.size();
        for (int i = -m; i < -1; i++) {
            for (int j = sz; j >= 0; j -= m) {
                int idx = j + i;
                if (idx >= 0) {
                    op.push_back({v[idx], v[idx + 1] - v[idx]});
                    if (last == -1 || last >= v[idx]) {
                        cost += v[idx + 1] - v[idx];
                    } else {
                        cost += 1000 + v[idx + 1] - v[idx];
                    }
                    last = v[idx];
                }
            }
        }

        vector<int> new_v;
        for (int i = sz - 1; i >= 0; i -= m) {
            new_v.push_back(v[i]);
        }
        reverse(new_v.begin(), new_v.end());
        v = new_v;
    }
    debug(cost);
    cout << op.size() << '\n';
    for (auto it : op) {
        cout << it[0] << ' ' << it[1] << '\n';
    }
}