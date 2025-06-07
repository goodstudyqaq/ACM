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
    int n, l;
    cin >> n >> l;

    vector<int> a(n - 1);
    map<int, int> M;
    M[0]++;
    int sum = 0;
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i];
        sum += a[i];
        sum %= l;
        M[sum]++;
    }

    if (l % 3) {
        cout << 0 << '\n';
        return 0;
    }

    int len = l / 3;

    long long ans = 0;
    for (int i = 0; i < len; i++) {
        ans += 1LL * M[i] * M[i + len] * M[i + 2 * len];
    }
    cout << ans << '\n';
}