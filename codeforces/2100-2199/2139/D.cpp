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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> stk;
    vector<int> l(n, -1), r(n, n);
    for (int i = 0; i < n; i++) {
        debug(i, stk);
        while (stk.size() && a[i] > a[stk.back()]) {
            stk.pop_back();
        }
        if (stk.size()) {
            l[i] = stk.back();
        }
        stk.push_back(i);
    }

    stk.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (stk.size() && a[i] < a[stk.back()]) {
            stk.pop_back();
        }
        if (stk.size()) {
            r[i] = stk.back();
        }
        stk.push_back(i);
    }

    vector<int> dp(n, n);
    debug(l, r);
    for (int i = 0; i < n; i++) {
        int _l = l[i], _r = r[i];
        if (_l != -1) {
            dp[_l] = min(dp[_l], _r - 1);
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        dp[i] = min(dp[i], dp[i + 1]);
    }

    debug(dp);

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (dp[l] >= r) {
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