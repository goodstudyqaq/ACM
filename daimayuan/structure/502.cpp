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

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> V(n + 1);
    vector<vector<int>> bigV(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    int B = 500;

    vector<int> big(n + 1);
    for (int i = 1; i <= n; i++) {
        if (V[i].size() >= B) big[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (auto v : V[i]) {
            if (big[v]) {
                bigV[i].push_back(v);
            }
        }
    }

    vector<int> color(n + 1);  // 0 白色 1 黑色

    vector<int> ans(n + 1);
    while (q--) {
        int ty, x;
        cin >> ty >> x;
        if (ty == 1) {
            for (auto v : bigV[x]) {
                if (color[x]) {
                    ans[v]--;
                } else {
                    ans[v]++;
                }
            }
            color[x] ^= 1;
        } else {
            if (big[x]) {
                cout << ans[x] << '\n';
            } else {
                int res = 0;
                for (auto v : V[x]) {
                    if (color[v]) res++;
                }
                cout << res << '\n';
            }
        }
    }
}