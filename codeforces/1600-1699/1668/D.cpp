#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

#define lowbit(x) x & -x

const int maxn = 5e5 + 5;
int mx[maxn];

void update(int idx, int val) {
    while (idx < maxn) {
        mx[idx] = max(mx[idx], val);
        idx += lowbit(idx);
    }
}

int query(int idx) {
    int res = -1e9 - 5;
    while (idx) {
        res = max(res, mx[idx]);
        idx -= lowbit(idx);
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<long long> a, sum;
    a.resize(n + 1);
    sum.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    if (sum[n] > 0) {
        cout << n << endl;
        return;
    }

    vector<long long> x = sum;

    sort(x.begin(), x.end());
    int xcnt = unique(x.begin(), x.end()) - x.begin();
    for (int i = 0; i <= n; i++) {
        sum[i] = lower_bound(x.begin(), x.begin() + xcnt, sum[i]) - x.begin() + 1;
    }
    for (int i = 1; i <= xcnt; i++) {
        mx[i] = -1e9 - 1;
    }
    // debug(sum);
    // debug(sum[0]);
    update(sum[0], 0);
    vector<int> dp(n + 1);

    for (int i = 1; i <= n; i++) {
        dp[i] = max(dp[i - 1] + (a[i] > 0 ? 1 : a[i] < 0 ? -1
                                                         : 0),
                    i + query(sum[i] - 1));
        update(sum[i], dp[i] - i);
    }
    // debug(sum);
    // debug(dp);
    cout << dp[n] << endl;
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