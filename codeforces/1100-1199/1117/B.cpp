#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    int mx1 = a[n - 1], mx2 = a[n - 2];

    // k 次 mx1 1 次 mx2

    if (mx1 == mx2) {
        cout << 1LL * mx1 * m << endl;
    } else {
        int times = m / (k + 1);
        long long sum = 1LL * k * mx1 + mx2;
        long long res = sum * times;

        res += 1LL * (m % (k + 1)) * mx1;
        cout << res << endl;
    }
}