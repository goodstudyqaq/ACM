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
    vector<int> c(n + 1);
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        cnt[c[i]]++;
    }
    vector<vector<int>> V(n + 1);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    vector<int> sz(n + 1), big(n + 1);

    function<void(int, int)> dfs0 = [&](int u, int pre) {
        sz[u] = 1;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs0(v, u);
            if (!big[u] || sz[big[u]] < sz[v]) big[u] = v;
        }
    };
    dfs0(1, -1);
    // debug(sz, big);
    

    long long res = 0;
    function<void(int, int, map<int, int>&)> dfs1 = [&](int u, int pre, map<int, int>&ans) {
        if (big[u]) {
            dfs1(big[u], u, ans);
        }
        for (auto v : V[u]) {
            if (v == pre || v == big[u]) continue;
            map<int, int> ans2;
            dfs1(v, u, ans2);

            if (ans.size() < ans2.size()) {
                swap(ans, ans2);
            }

            for (auto it : ans2) {
                int color = it.first;
                int num = it.second;
                if (cnt[color] == 1) continue;
                if (color != c[u]) {
                    res += 1LL * num * ans[color];
                }
                ans[color] += num;
            }
        }
        res += ans[c[u]];
        ans[c[u]] = 1;
    };

    map<int, int> ans;
    dfs1(1, -1, ans);
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