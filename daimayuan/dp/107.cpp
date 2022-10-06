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
    vector<ll> a(n + 1);
    vector<int> t(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }
    vector<vector<int>> V(n + 1);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<ll> f(n + 1);
    vector<ll> sum_f(n + 1);
    function<void(int, int)> dfs = [&](int u, int pre) {
        int mx = 0;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
            sum_f[u] += f[v];
            mx = max(1LL * mx, a[v]);
        }
        // 第一种
        f[u] = sum_f[u] + mx;

        // 第二种
        pair<int, int> mx1(0, -1), mx2(0, -1);
        for (auto v : V[u]) {
            if (v == pre) continue;
            if (t[v] == 3) {
                pii tmp = {a[v], v};
                if (tmp > mx2) swap(tmp, mx2);
                if (mx2 > mx1) swap(mx2, mx1);
            }
        }

        for (auto v : V[u]) {
            if (v == pre) continue;
            ll tmp = a[v] + sum_f[v];
            if (v == mx1.second) {
                tmp += mx2.first;
            } else {
                tmp += mx1.first;
            }
            tmp += sum_f[u];
            tmp -= f[v];
            f[u] = max(f[u], tmp);
        }
        debug(u, f[u]);
    };

    dfs(1, -1);
    debug(f);

    cout << f[1] + a[1] << endl;
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