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
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    int ans = 0;

    auto work = [&](int n, int a, int flag) {
        int ans = 0;
        int mi = n;
        if (flag) {
            mi = min(a, n - a + 1);
            n = mi;
            a = 1 + n >> 1;
            ans++;
        } else {
            a = 1 + n >> 1;
        }
        while (mi > 1) {
            // debug(mi, a);
            ans++;
            mi = min(a, n - a + 1);
            n = mi;
            a = 1 + n >> 1;
        }
        // debug(ans);
        return ans;
    };
    int ans1 = work(n, a, 1) + work(m, b, 0);
    debug(ans1);
    int ans2 = work(n, a, 0) + work(m, b, 1);
    debug(ans2);
    cout << min(ans1, ans2) << '\n';
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