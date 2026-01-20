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
    if (n == 1) {
        cout << 1 << '\n';
    } else if (n == 2) {
        cout << 9 << '\n';
    } else {
        int val = n * n;
        int ans = val + val - 1 + val - 2 + val - 1 - n;

        val = n * n - 1 - n;
        int ans2 = val + val - 1 + val + 1 + val + val;

        cout << max(ans, ans2) << '\n';
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