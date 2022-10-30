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
    vector<int> a(n + 1);
    vector<vector<int>> V(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];

        int tmp = i - a[i];
        if (tmp > 0) {
            V[tmp].push_back(i);
        }
    }
    vector<int> dp(n + 1, -1);

    function<bool(int)> dfs = [&](int now) -> bool {
        if (now > n) return true;
        if (dp[now] != -1) return dp[now];
        int val = a[now];
        if (now + val <= n) {
            bool f = dfs(now + val + 1);
            if (f) return dp[now] = f;
        }

        for (auto it : V[now]) {
            bool f = dfs(it + 1);
            if (f) return dp[now] = f;
        }
        return dp[now] = false;
    };

    if (dfs(1)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
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