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

typedef array<int, 3> a3;
void solve() {
    int n;
    cin >> n;
    vector<vector<a3>> V(n + 1);
    vector<vector<int>> dp(n + 1, vector<int>(20));
    vector<int> dep(n + 1);
    vector<ll> val_a(n + 1), val_b(n + 1);
    for (int i = 2; i <= n; i++) {
        int p, a, b;
        cin >> p >> a >> b;
        V[p].push_back({i, a, b});
        dp[i][0] = p;
    }

    function<void(int, int, ll, ll)> dfs = [&](int u, int d, ll now_val_a, ll now_val_b) {
        // debug(u, d, now_val_a, now_val_b);

        dep[u] = d;
        val_a[u] = now_val_a;
        val_b[u] = now_val_b;
        for (auto v : V[u]) {
            dfs(v[0], d + 1, now_val_a + v[1], now_val_b + v[2]);
        }
    };
    dfs(1, 0, 0, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++) {
            if ((1 << i) > dep[j]) continue;
            int k = dp[j][i - 1];
            dp[j][i] = dp[k][i - 1];
        }
    auto work = [&](int idx) -> int {
        ll the_val_a = val_a[idx];
        ll the_val_b = val_b[idx];
        if (the_val_b <= the_val_a) {
            return dep[idx];
        }

        int now = idx;
        for (int i = 19; i >= 0; i--) {
            if ((1 << i) > dep[idx]) continue;
            int k = dp[now][i];
            if (val_b[k] > the_val_a) {
                now = k;
            }
        }
        now = dp[now][0];
        // debug(idx, now);
        return dep[now];
    };

    for (int i = 2; i <= n; i++) {
        int ans = work(i);
        cout << ans << ' ';
    }
    cout << endl;
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