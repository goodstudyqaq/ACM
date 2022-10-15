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

vector<int> v;

ll dp[17][10][4][2];
ll dfs(int d, int last_num, int last_len, bool exist, bool limit, bool lead) {
    if (d == -1) {
        return exist;
    }
    if (!limit && dp[d][last_num][last_len][exist] != -1) {
        return dp[d][last_num][last_len][exist];
    }
    ll ans = 0;

    int LIMIT = limit ? v[d] : 9;
    for (int i = 0; i <= LIMIT; i++) {
        if (i == 0 && lead) {
            ans += dfs(d - 1, 0, 0, 0, false, true);
        } else {
            if (i > last_num) {
                int len2 = min(last_len + 1, 3);
                bool e = exist | (len2 == 3);
                ans += dfs(d - 1, i, len2, e, limit && (i == LIMIT), false);
            } else {
                ans += dfs(d - 1, i, 1, exist, limit && (i == LIMIT), false);
            }
        }
    }
    if (!limit) dp[d][last_num][last_len][exist] = ans;
    return ans;
}

ll solve(ll num) {
    v.clear();
    while (num) {
        v.push_back(num % 10);
        num /= 10;
    }
    int n = v.size();
    return dfs(n - 1, 0, 0, 0, true, true);
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    memset(dp, -1, sizeof(dp));
    ll l, r;
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;

    return 0;
}