#include <bits/stdc++.h>

#include <functional>

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
    int a, b;
    cin >> a >> b;

    vector<vector<int>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        V[x].push_back(y);
        V[y].push_back(x);
    }

    vector<int> dep(n + 1), fa(n + 1);
    function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
        dep[u] = d;
        fa[u] = pre;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u, d + 1);
        }
    };

    dfs(a, -1, 0);

    int db = dep[b];
    int go_num = db / 2;

    long long ans = go_num;
    debug(ans);

    int now = b;
    while (go_num) {
        b = fa[b];
        go_num--;
    }
    int rt = b;
    if (db % 2) {
        rt = fa[b];
    }
    debug(rt);

    vector<long long> dp(n + 1), dp2(n + 1);
    function<void(int, int)> dfs2 = [&](int u, int pre) {
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs2(v, u);
            dp[u] += dp[v] + 2;
        }
        dp2[u] = 1e9;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dp2[u] = min(dp2[u], dp[u] - dp[v] - 2 + dp2[v] + 1);
        }
        if (dp2[u] == 1e9) dp2[u] = 0;
    };

    dfs2(rt, -1);
    debug(dp2[rt]);

    ans += dp2[rt];
    if (db % 2) ans++;
    cout << ans << endl;
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