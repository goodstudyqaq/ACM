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
    int n, k;
    cin >> n >> k;

    int l = 1, r = n - 1;
    int ans = 0;
    
    auto get_val = [&](int m) -> long long {
        long long left = 1LL * (1 + m) * m / 2 + 1LL * (k - 1) * m;
        long long right = 1LL * (m + 1 + n) * (n - m) / 2 + 1LL * (k - 1) * (n - m);
        return abs(right - left);
    };

    while (l <= r) {
        int m = l + r >> 1;
        if (get_val(m) > get_val(m + 1)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    cout << get_val(ans + 1) << endl;

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