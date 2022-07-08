#include <bits/stdc++.h>

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
    vector<vector<int>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    if (n == 1) {
        cout << 0 << endl;
        return;
    }

    int mx_sz = 0;
    for (int i = 1; i <= n; i++) {
        mx_sz = max(mx_sz, (int)V[i].size());
    }

    if (mx_sz <= 2) {
        cout << 1 << endl;
        return;
    }

    function<int(int, int)> dfs = [&](int u, int pre) -> int {
        int a = 0, b = 0;
        for (auto v : V[u]) {
            if (v == pre) continue;
            int tmp = dfs(v, u);
            if (tmp) {
                a += tmp;
            } else {
                b++;
            }
        }
        return a + max(0, b - 1);
    };

    for (int i = 1; i <= n; i++) {
        if (V[i].size() >= 3) {
            cout << dfs(i, -1) << endl;
            return;
        }
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
}