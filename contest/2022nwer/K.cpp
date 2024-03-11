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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, k;
    cin >> n >> k;
    vector<set<int>> V(k + 1);
    for (int i = 1; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].insert(v);
        V[v].insert(u);
    }

    for (int i = 1; i <= k; i++) {
        int g = 0;
        for (auto v : V[i]) {
            if (v == i) continue;
            if (V[v].size() > 1) {
                g++;
            }
        }
        if (g > 2) {
            cout << "impossible" << endl;
            return 0;
        }
    }

    vector<int> vis(k + 1);

    function<int(int, int)> dfs = [&](int u, int pre) -> int {
        vis[u] = 1;
        int flag = 0;
        for (auto v : V[u]) {
            if (v == pre) continue;
            if (v == u) continue;
            if (vis[v] == 0) {
                flag |= dfs(v, u); // 只要有一个环就返回 1
            } else if (vis[v] == 1) {
                flag = 1;
            } else {
                continue;
            }
        }
        vis[u] = 2;
        return flag;
    };

    int cir_num = 0;
    int times = 0;
    for (int i = 1; i <= k; i++) {
        if (vis[i] == 0 && V[i].size() > 0) {
            times++;
            int flag = dfs(i, -1);
            if (flag == 1) {
                cir_num++;
            }
        }
    }
    debug(cir_num, times);
    if (cir_num == 0 || times == 1) {
        cout << "possible" << endl;
    } else {
        cout << "impossible" << endl;
    }
    return 0;
}