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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> V(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        V[p].push_back(i);
    }

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    map<pii, ll> M;

    const ll inf = numeric_limits<ll>::max() / 2;
    function<ll(int, int)> dfs = [&](int u, int k) -> ll {
        if (M.count({u, k})) return M[{u, k}];

        int sz = V[u].size();
        if (sz == 0) {
            return 1LL * k * s[u];
        }
        int nxt_k = k / sz;
        int num = k % sz;  // 有 num 个孩子多 1

        ll ans = 1LL * k * s[u];

        if (num == 0) {
            for (int i = 0; i < sz; i++) {
                ans += dfs(V[u][i], nxt_k);
            }
            return M[{u, k}] = ans;
        } else {
            vector<pair<ll, int>> tmp(sz);
            vector<ll> X(sz);
            for (int i = 0; i < sz; i++) {
                int v = V[u][i];
                ll x = dfs(v, nxt_k);
                ll y = dfs(v, nxt_k + 1);
                X[i] = x;
                tmp[i] = {y - x, i};
            }
            sort(tmp.begin(), tmp.end(), greater<pair<ll, int>>());
            for (int i = 0; i < num; i++) {
                ans += X[tmp[i].second] + tmp[i].first;
            }
            for (int i = num; i < sz; i++) {
                int idx = tmp[i].second;
                ans += X[idx];
            }
            return M[{u, k}] = ans;
        }
    };
    cout << dfs(1, k) << endl;
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