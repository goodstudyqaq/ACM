#include <bits/stdc++.h>

#include <algorithm>
#include <cwchar>
#include <functional>
#include <limits>
#include <queue>

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
    int n, k;
    cin >> n >> k;

    vector<long long> d(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    reverse(d.begin() + 1, d.begin() + 1 + n);

    int m = n / (k + 1);
    debug(m);

    priority_queue<long long, vector<long long>, greater<long long>> Q;
    for (int i = 0; i < m; i++) {
        int beg = (i + 1) * (k + 1);
        int end = min(beg + k, n);
        int sz = end - beg + 1;
        if (sz == 0) break;
        debug(i, beg, end, sz);

        vector<long long> tmp(end - beg + 1), sum(end - beg + 1);
        for (int j = beg; j <= end; j++) {
            tmp[j - beg] = d[j];
        }
        sort(tmp.begin(), tmp.end());
        reverse(tmp.begin(), tmp.end());

        Q.push(tmp[0]);
        for (int j = 1; j < sz; j++) {
            long long val = Q.top();
            if (val < tmp[j]) {
                Q.pop();
                Q.push(tmp[j]);
            } else {
                break;
            }
        }
    }

    long long ans = 0;
    while (!Q.empty()) {
        long long val = Q.top();
        ans += val;
        Q.pop();
    }
    cout << ans << '\n';
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