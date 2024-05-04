#include <bits/stdc++.h>

#include <numeric>

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
    vector<long long> a(n);
    long long mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }

    auto check = [&](long long val) {
        long long ct = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] < val) ct += val - a[i];
        }

        return ct <= k;
    };

    long long l = 1, r = 2e12;
    long long ans = 1;
    while (l <= r) {
        long long m = l + r >> 1;
        if (check(m)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (a[i] < ans) {
            k -= ans - a[i];
            a[i] = ans;
        }
    }

    int small = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == ans) {
            small++;
        }
    }
    small -= k;

    long long res = 1LL * n * ans - n + 1 + (n - small);
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