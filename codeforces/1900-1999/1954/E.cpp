#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
struct DSU {
    std::vector<int> f;
    DSU(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        if (f[x] == x) {
            return x;
        }
        int y = leader(f[x]);
        f[x] = y;
        return f[x];
    }
    bool merge(int a, int b) {
        auto x = leader(a);
        auto y = leader(b);
        if (x == y) {
            return false;
        }
        f[x] = y;
        return true;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<int> a(n + 1);
    int mx = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    vector<int> num(mx + 1);

    vector<vector<int>> IDX(mx + 1);
    for (int i = 1; i <= n; i++) {
        IDX[a[i]].push_back(i);
    }

    DSU dsu(n + 1);

    vector<int> valid(n + 2);
    set<int> S;

    for (int i = mx; i >= 1; i--) {
        for (auto idx : IDX[i]) {
            valid[idx] = 1;
        }

        for (auto idx : IDX[i]) {
            if (valid[idx + 1]) {
                S.erase(dsu.leader(idx + 1));
                S.erase(dsu.leader(idx));
                dsu.merge(idx, idx + 1);
            }
            if (valid[idx - 1]) {
                S.erase(dsu.leader(idx));
                S.erase(dsu.leader(idx - 1));
                dsu.merge(idx - 1, idx);
            }
            S.insert(dsu.leader(idx));
        }
        num[i] = S.size();
        debug(i, S);
    }
    debug(num);

    for (int i = 1; i <= mx; i++) {
        long long ans = 0;
        for (int j = 1; j <= mx; j += i) {
            ans += num[j];
        }
        cout << ans << ' ';
    }
    cout << endl;
}