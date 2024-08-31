#include <bits/stdc++.h>

#include <limits>

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
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> V(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        V[p].push_back(i);
        V[i].push_back(p);
    }

    vector<long long> dp(n);
    const long long inf = numeric_limits<long long>::max() / 2;
    function<void(int, int)> dfs = [&](int u, int pre) {
        long long mi = inf;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
            mi = min(mi, dp[v]);
        }
        if (mi == inf) {
            dp[u] = a[u];
        } else {
            if (a[u] < mi) {
                dp[u] = (a[u] + mi) >> 1;
            } else {
                dp[u] = mi;
            }
        }
    };
    dfs(0, -1);

    long long mi = inf;
    for (auto v : V[0]) {
        mi = min(mi, dp[v]);
    }
    cout << a[0] + mi << endl;

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