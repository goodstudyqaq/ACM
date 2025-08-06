#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    vector<vector<int>> V(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    if (n == 2) {
        cout << "NO" << endl;
        return;
    }

    int special = -1;
    function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
        for (auto v : V[u]) {
            if (v == pre) continue;
            if (d % 2 == 0) {
                cout << u << ' ' << v << endl;
            } else {
                cout << v << ' ' << u << endl;
            }

            if (v == special) {
                dfs(v, u, d);
            } else {
                dfs(v, u, d ^ 1);
            }

        }
    };

    bool flag = false;
    int rt = -1;
    for (int i = 1; i <= n; i++) {
        if (V[i].size() == 2) {
            special = i;
            flag = true;
            rt = V[i][0];
        }
    }

    if (!flag) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    dfs(rt, -1, 0);
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