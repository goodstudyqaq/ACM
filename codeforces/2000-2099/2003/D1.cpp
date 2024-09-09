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
    int n, m;
    cin >> n >> m;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;
        set<int> S;
        for (int j = 0; j < l; j++) {
            int a;
            cin >> a;
            S.insert(a);
        }

        int now = 0;
        while (S.count(now)) now++;
        now++;
        while (S.count(now)) now++;
        mx = max(mx, now);
    }
    debug(mx);

    int limit = min(m, mx);

    long long ans = 1LL * (limit + 1) * mx;
    if (m - limit > 0) {
        ans += 1LL * (mx + 1 + m) * (m - mx) / 2;
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