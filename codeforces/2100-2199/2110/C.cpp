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
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }

    int nowl = 0, nowr = 0;

    vector<int> ans(n);
    vector<pair<int, int>> interval(n);

    auto work = [&](int l1, int r1, int l2, int r2) -> pair<int, int> {
        if (r1 < l2) return {-1, -1};
        if (r2 < l1) return {-1, -1};
        return {max(l1, l2), min(r1, r2)};
    };

    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
        } else if (a[i] == 1) {
            nowl++;
            nowr++;
        } else {
            nowr++;
        }
        interval[i] = work(nowl, nowr, l[i], r[i]);
        if (interval[i].first == -1) {
            cout << -1 << '\n';
            return;
        }
        nowl = interval[i].first;
        nowr = interval[i].second;
    }
    debug(interval);

    int now = interval[n - 1].first;
    ans[n - 1] = now;

    for (int i = n - 1; i >= 1; i--) {
        if (a[i] == 0) {
            ans[i - 1] = ans[i];
        } else if (a[i] == 1) {
            ans[i - 1] = ans[i] - 1;
        } else {
            int val = ans[i];
            if (interval[i - 1].first <= val && val <= interval[i - 1].second) {
                ans[i - 1] = val;
            } else {
                ans[i - 1] = val - 1;
            }
        }
    }

    now = 0;
    for (int i = 0; i < n; i++) {
        if (ans[i] == now) {
            cout << 0 << ' ';
        } else {
            cout << 1 << ' ';
        }
        now = ans[i];
        // debug(ans[i]);
    }
    cout << '\n';
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