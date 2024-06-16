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

void solve() {
    long long n, a, b;
    cin >> n >> a >> b;

    long long mid = max(b - a, 0LL);
    long long mi = min(n, b);
    mid = min(mid, mi);
    mid = max(mid, 0LL);

    long long ans = 0;
    for (long long k = mid - 3; k <= mid + 3; k++) {
        if (k < 0) continue;
        if (k > b) continue;
        if (k > n) continue;
        long long tmp = (b * 2 - k + 1) * k / 2 + (n - k) * a;
        ans = max(ans, tmp);
    }
    cout << ans << endl;
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