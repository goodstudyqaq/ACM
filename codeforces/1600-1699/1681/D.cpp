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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    ll x;
    cin >> n >> x;
    if (x == 1) {
        cout << -1 << endl;
        return 0;
    }
    map<ll, int> dp;

    auto get_num = [&](ll now) {
        vector<int> v;
        while (now) {
            v.push_back(now % 10);
            now /= 10;
        }
        return v;
    };

    function<int(ll)> dfs = [&](ll now) -> int {
        // debug(now);
        if (dp.count(now)) return dp[now];
        vector<int> v = get_num(now);
        if (v.size() == n) {
            return dp[now] = 0;
        } else if (v.size() > n) {
            return dp[now] = 100;
        }
        int res = 100;

        for (auto it : v) {
            if (it == 1) continue;
            res = min(res, dfs(now * it) + 1);
        }
        return dp[now] = res;
    };
    int ans = dfs(x);
    if (ans == 100) ans = -1;

    cout << ans << endl;
}