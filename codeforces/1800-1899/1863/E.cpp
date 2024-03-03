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
    int n, m, k;
    cin >> n >> m >> k;
    vector<long long> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    vector<vector<int>> V(n), revV(n);
    vector<int> out(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[v].push_back(u);
        out[v]++;
        revV[u].push_back(v);
    }
    vector<pll> ans(n);
    queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (out[i] == 0) {
            Q.push(i);
            ans[i] = {0, h[i]};
        }
    }

    auto get_mx = [&](pll now, ll _h, pll pre) -> pll {
        if (pre.second <= _h) {
            return {max(pre.first, now.first), _h};
        } else {
            return {max(pre.first + 1, now.first), _h};
        }
    };

    while (!Q.empty()) {
        auto u = Q.front();
        Q.pop();
        for (auto it : revV[u]) {
            out[it]--;
            ans[it] = get_mx(ans[it], h[it], ans[u]);
            if (out[it] == 0) {
                Q.push(it);
            }
        }
    }

    const ll inf = numeric_limits<ll>::max() / 2;
    ll mx = 0, mi = inf;
    for (int i = 0; i < n; i++) {
        ll tmp = ans[i].first * k + ans[i].second;
        mx = max(mx, tmp);
        mi = min(mi, tmp);
    }
    debug(mi, mx);

    long long res = mx - mi;

    vector<int> f;
    for (int i = 0; i < n; i++) {
        if (V[i].size() == 0) {
            f.push_back(i);
        }
    }

    sort(f.begin(), f.end(), [&](int x, int y) {
        return h[x] < h[y];
    });

    function<ll(int)> dfs = [&](int u) {
        long long res = ans[u].first * k + ans[u].second;
        for (auto v : revV[u]) {
            auto it = get_mx(ans[v], h[v], ans[u]);
            if (it != ans[v]) {
                ans[v] = it;
                res = max(res, dfs(v));
            }
        }
        return res;
    };

    int sz = f.size();
    for (int i = 0; i < sz - 1; i++) {
        int idx = f[i + 1];
        mi = ans[idx].first * k + ans[idx].second;
        idx = f[i];
        // ans[idx].first++
        ans[idx].first++;
        mx = max(mx, dfs(idx));
        // debug(i, mi, mx);
        res = min(res, mx - mi);
    }
    cout << res << endl;
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