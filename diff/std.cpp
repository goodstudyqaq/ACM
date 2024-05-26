#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

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
    vector<vector<int>> g(3, vector<int>(n));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }
    vector<vector<int>> V(2 * n + 1);

    for (int i = 0; i < n; i++) {
        // set<int> S;
        // for (int j = 0; j < 3; j++) {
        //     S.insert(abs(g[j][i]));
        // }
        // if (S.size() == 1) {
        //     int small = 0;
        //     for (int j = 0; j < 3; j++) {
        //         if (g[j][i] < 0) {
        //             small++;
        //         }
        //     }
        //     int u = abs(g[0][i]);
        //     if (small <= 1) {
        //         // 选 1
        //         V[n + u].push_back(u);
        //     } else {
        //         // 选 -1
        //         V[u].push_back(n + u);
        //     }
        // } else if (S.size() == 2) {
        //     for (int p = 0; p < 3; p++) {
        //         for (int q = 0; q < 3; q++) {
        //             if (p == q) continue;
        //             if (abs(g[p][i]) == abs(g[q][i])) {
        //                 int u = abs(g[p][i]);
        //                 if (g[p][i] == g[q][i]) {
        //                     if (g[p][i] > 0) {
        //                         // 选 1
        //                         V[n + u].push_back(u);
        //                     } else {
        //                         // 选 -1
        //                         V[u].push_back(n + u);
        //                     }
        //                 } else {
        //                     // 另一个数一定是 1
        //                     for (int k = 0; k < 3; k++) {
        //                         if (k != p && k != q) {
        //                             int u = abs(g[k][i]);
        //                             V[n + u].push_back(u);
        //                             break;
        //                         }
        //                     }
        //                 }
        //                 p = 10;
        //                 break;
        //             }
        //         }
        //     }
        // } else {
        for (int p = 0; p < 3; p++) {
            for (int q = 0; q < 3; q++) {
                if (p == q) continue;
                int idx1 = g[p][i] > 0 ? g[p][i] + n : abs(g[p][i]);
                int idx2 = g[q][i] > 0 ? g[q][i] : n + abs(g[q][i]);
                V[idx1].push_back(idx2);
            }
        }
        // }
    }
    // debug(V);

    auto check = [&]() {
        vector<int> vis(2 * n + 1);
        vector<int> s;
        vector<int> cnt(2 * n + 1);

        function<bool(int)> dfs = [&](int u) {
            int u2 = u > n ? u - n : u + n;
            if (vis[u2]) return false;
            if (vis[u]) return true;
            vis[u] = 1;
            cnt[u] += 1;
            s.push_back(u);
            for (auto v : V[u]) {
                if (!dfs(v)) return false;
            }
            return true;
        };

        bool flag = true;

        for (int i = 1; i <= n; i++) {
            if (!vis[i] && !vis[i + n]) {
                s.clear();
                if (!dfs(i)) {
                    while (s.size()) {
                        vis[s.back()] = 0;
                        s.pop_back();
                    }
                    if (!dfs(i + n)) {
                        flag = false;
                        break;
                    }
                }
            }
        }

        for (int i = 1; i <= 2 * n; i++) {
            if (cnt[i] > 2) return false;
        }

        return flag;
    };

    if (check()) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
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