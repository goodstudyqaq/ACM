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

const int mod = 998244353;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1);
    vector<vector<ll>> ans(n + 1, vector<ll>(n + 1, 0));
    vector<vector<bool>> big(n + 1, vector<bool>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ans[i][0] = a[i];
        if (ans[i][0] >= n) big[i][0] = true;
        ans[i][0] %= mod;
    }

    vector<vector<int>> V(n + 1);
    vector<int> in(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        in[v]++;
    }

    queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            Q.push(i);
        }
    }

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto v : V[u]) {
            for (int i = 0; i < n; i++) {
                if (ans[u][i] > 0 || big[u][i]) {
                    ans[v][i + 1] += ans[u][i];
                    big[v][i + 1] = big[v][i + 1] | big[u][i];
                    if (ans[v][i + 1] >= n) big[v][i + 1] = true;
                    ans[v][i + 1] %= mod;
                }
            }
            in[v]--;
            if (in[v] == 0) {
                Q.push(v);
            }
        }
    }

    // debug(ans);
    // debug(big);

    for (int i = 1; i <= n; i++) {
        if (V[i].size() == 0) {
            ll res = 0;
            bool flag = false;
            for (int j = 0; j <= n; j++) {
                if (ans[i][j] || big[i][j]) {
                    if (!flag) {
                        res = max(res, 1LL * j);
                    }
                    res += ans[i][j];
                    if (res >= n || big[i][j]) flag = true;
                    res %= mod;
                }
            }
            cout << res % mod << endl;
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