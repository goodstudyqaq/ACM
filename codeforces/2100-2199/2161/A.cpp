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
    int r0, x, d, n;
    cin >> r0 >> x >> d >> n;
    string s;
    cin >> s;
    int now = r0;
    int ans = 0;
    for (auto it : s) {
        if (it == '1') {
            ans += 1;
            now -= d;
            now = max(now, 0);
        } else {
            if (now < x) {
                ans += 1;
                now -= d;
                now = max(now, 0);
            }
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