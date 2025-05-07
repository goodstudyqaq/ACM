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
    long long n, k;
    long long x;
    cin >> n >> k >> x;
    vector<long long> a(n);
    long long sum = 0;
    vector<long long> suma(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        suma[i] = a[i];
        if (i != n - 1) suma[i] += suma[i + 1];
    }


    if (sum * k < x) {
        cout << 0 << '\n';
        return;
    }

    long long l = 0, r = 1LL * n * k - 1;
    long long ans = 1LL * n * k;

    auto check = [&](long long idx) {
        long long idx2 = idx % n;
        long long times = idx / n;
        long long val = suma[idx2] + 1LL * (k - times - 1) * sum;

        if (val < x) return true;
        return false;
    };

    while (l <= r) {
        long long mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
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