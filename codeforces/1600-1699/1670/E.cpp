#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
typedef pair<int, int> pii;

void solve() {
    int p;
    cin >> p;
    int n = 1 << p;
    vector<vector<pii>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back({v, i});
        V[v].push_back({u, i});
    }

    int L = 1, R = 1 << p;
    int rt = 1;

    vector<int> ans(n + 1);
    vector<int> ans2(n);
    int LIMIT = 1 << p;

    function<void(int, int, int)> dfs = [&](int u, int pre, int now) {
        if (u == rt) {
            ans[u] = R;
            R++;
        } else {
            if (now % 4 == 0 || now % 4 == 3) {
                ans[u] = R++;
            } else {
                ans[u] = L++;
            }
        }
        now++;
        for (auto v : V[u]) {
            if (v.first == pre) continue;
            if (now % 4 == 0 || now % 4 == 3) {
                ans2[v.second] = R++;
            } else {
                ans2[v.second] = L++;
            }
            dfs(v.first, u, now + 1);
        }
    };
    dfs(rt, 0, -1);

    int mx = 0;
    function<void(int, int, int)> dfs2 = [&](int u, int pre, int now) {
        now ^= ans[u];
        mx = max(mx, now);
        debug(u, pre, now, "aa");

        for (auto v : V[u]) {
            if (v.first == pre) continue;
            int nxt_now = now ^ ans2[v.second];
            mx = max(mx, nxt_now);
            dfs2(v.first, u, nxt_now);
        }
    };

    // dfs2(rt, 0, 0);
    debug(mx, LIMIT);

    cout << 1 << endl;
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    for (int i = 1; i < n; i++) {
        cout << ans2[i] << ' ';
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