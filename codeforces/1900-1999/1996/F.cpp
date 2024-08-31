#include <bits/stdc++.h>

#include <cassert>
#include <queue>

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
    long long n, k;
    cin >> n >> k;
    vector<long long> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    long long l = 0, r = 1e9 + 1;
    long long ans = -1;

    auto work = [&](long long m) -> long long {
        long long k = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] >= m) {
                long long diff = a[i] - m;
                k += (diff / b[i] + 1);
            }
        }
        return k;
    };

    while (l <= r) {
        int m = l + r >> 1;
        long long tmp = work(m);
        if (tmp <= k) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    debug(ans);
    assert(ans != -1);

    long long res = 0;
    priority_queue<pii> Q;
    for (int i = 1; i <= n; i++) {
        if (a[i] >= ans) {
            long long diff = a[i] - ans;
            long long times = diff / b[i] + 1;
            // a[i], a[i] - b[i] * (times - 1)
            res += 1LL * (1LL * a[i] + a[i] - 1LL * b[i] * (times - 1)) * times / 2;
            k -= times;
            a[i] -= b[i] * times;
            if (a[i] > 0) Q.push({a[i], i});
        } else {
            Q.push({a[i], i});
        }
    }

    while (k && Q.size()) {
        auto it = Q.top();
        Q.pop();
        res += it.first;
        int tmp = it.first - b[it.second];
        if (tmp > 0) {
            Q.push({tmp, it.second});
        }
        k--;
    }

    cout << res << endl;
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