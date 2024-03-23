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
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    int l = 1, r = n / (k + 1);

    auto check = [&](int cnt) -> bool {
        int num = 0;

        function<int(int, int)> dfs = [&](int u, int pre) -> int {
            int sz = 1;
            for (auto v : V[u]) {
                if (v == pre) continue;
                sz += dfs(v, u);
            }
            if (sz >= cnt) {
                num++;
                return 0;
            } else {
                return sz;
            }
        };
        int tmp = dfs(1, -1);
        if (num > k) return true;
        if (num == k) return tmp >= cnt;
        return false;
    };

    int ans = 1;
    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
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
    return 0;
}