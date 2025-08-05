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
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> p(n), d(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }

    map<long long, int> M;
    vector<vector<int>> go(n, vector<int>(2, -1));

    for (int i = n - 1; i >= 0; i--) {
        long long tmp = (p[i] - d[i]) % k;
        tmp = (tmp + k) % k;
        if (M.count(tmp)) {
            go[i][1] = M[tmp];
        }
        M[tmp] = i;
    }

    M.clear();
    for (int i = 0; i < n; i++) {
        long long tmp = (p[i] + d[i]) % k;
        tmp = (tmp + k) % k;
        if (M.count(tmp)) {
            go[i][0] = M[tmp];
        }
        M[tmp] = i;
    }
    debug(go);

    int q;
    cin >> q;
    vector<pll> query(q);
    for (int i = 0; i < q; i++) {
        cin >> query[i].first;
        query[i].second = i;
    }

    sort(query.begin(), query.end());

    int r = n - 1;

    vector<vector<int>> dp(n, vector<int>(2, -1));  // -1 没碰到过，0: 没有环，1 有环 2 在栈中

    function<bool(int, int)> dfs = [&](int u, int f) -> bool {
        if (dp[u][f] == 0 || dp[u][f] == 1) {
            return dp[u][f];
        } else if (dp[u][f] == 2) {
            return dp[u][f] = 1;
        } else {
            if (go[u][f] == -1) {
                return dp[u][f] = 0;
            }
            dp[u][f] = 2;
            int _go = go[u][f];
            return dp[u][f] = dfs(_go, f ^ 1);
        }
    };

    M.clear();
    vector<bool> ans(q);
    for (int i = q - 1; i >= 0; i--) {
        long long x = query[i].first;
        while (r >= 0 && p[r] >= x) {
            M[(((p[r] - d[r]) % k) + k) % k] = r;
            r--;
        }
        long long tmp = x % k;
        if (M.count(tmp)) {
            int idx = M[tmp];
            if (dfs(idx, 0)) {
                ans[query[i].second] = 0;
            } else {
                ans[query[i].second] = 1;
            }
        } else {
            ans[query[i].second] = 1;
        }
    }

    for (int i = 0; i < q; i++) {
        if (ans[i]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
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
    return 0;
}