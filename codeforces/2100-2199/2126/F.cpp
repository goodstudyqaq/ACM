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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    vector<vector<pii>> V(n);
    long long ans = 0;
    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        V[u].push_back({v, c});
        V[v].push_back({u, c});

        if (a[u] != a[v]) {
            ans += c;
        }
    }
    debug(ans);

    vector<map<int, long long>> cnt(n);

    vector<int> fa(n);
    vector<int> ct(n);
    function<void(int, int, int)> dfs = [&](int u, int pre, int cost) {
        fa[u] = pre;
        ct[u] = cost;
        for (auto v : V[u]) {
            if (v.first == pre) continue;
            cnt[u][a[v.first]] += v.second;
            dfs(v.first, u, v.second);
        }
    };
    dfs(0, -1, 0);

    while (q--) {
        int v, x;
        cin >> v >> x;
        v--, x--;
        if (a[v] != x) {
            ans += cnt[v][a[v]];
            if (fa[v] != -1 && a[fa[v]] == a[v]) {
                ans += ct[v];
            }
            if (fa[v] != -1) {
                cnt[fa[v]][a[v]] -= ct[v];
            }

            a[v] = x;
            ans -= cnt[v][a[v]];
            if (fa[v] != -1 && a[fa[v]] == a[v]) {
                ans -= ct[v];
            }
            if (fa[v] != -1) {
                cnt[fa[v]][a[v]] += ct[v];
            }
        }
        cout << ans << endl;
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
    return 0;
}