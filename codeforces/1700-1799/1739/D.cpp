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

    int ct = 0;
    function<int(int, int)> dfs = [&](int u, int max_depth) -> int {
        int mx = 0;
        for (auto it : V[u]) {
            int tmp = dfs(it, max_depth) + 1;
            if (tmp == max_depth) {
                if (u != 1) {
                    ct++;
                }
            } else {
                mx = max(mx, tmp);
            }
        }
        return mx;
    };

    auto check = [&](int max_depth) {
        ct = 0;
        dfs(1, max_depth);
        return ct <= k;
    };

    int l = 1, r = n - 1;
    int ans = -1;

    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
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
}