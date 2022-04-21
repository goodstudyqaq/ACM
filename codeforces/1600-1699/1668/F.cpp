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

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    bool ok = true;

    vector<bool> parity(n + 1);
    function<void(int, int)> dfs1 = [&](int u, int pre) {
        vector<int> cnt(2);
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs1(v, u);
            cnt[parity[v]]++;
        }
        if (u != 1) {
            parity[u] = (cnt[0] >= cnt[1]);
            cnt[parity[u]]++;
        }
        if (cnt[1] == cnt[0] || cnt[1] == cnt[0] + 1) {
        } else {
            ok = false;
        }
    };

    dfs1(1, 0);
    if (!ok) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;

    function<void(int, int)> solve = [&](int u, int pre) {
        vector<int> v2[2];
        for (auto v : V[u]) {
            if (v == pre) {
                v2[parity[u]].push_back(u);
            } else {
                v2[parity[v]].push_back(v);
            }
        }

        int sz = V[u].size();
        bool f = sz % 2;
        for (int i = 0; i < sz; i++) {
            int it = v2[f].back();
            v2[f].pop_back();
            if (it == u) {
                cout << u << ' ' << pre << endl;
            } else {
                solve(it, u);
            }
            f ^= 1;
        }
    };
    solve(1, 0);
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}