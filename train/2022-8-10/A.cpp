#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
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
    vector<ull> val(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ll a;
            cin >> a;
            val[i] += a * j;
        }
    }

    for (int i = 1; i < n; i++) {
        if (val[i] != val[i + 1]) {
            if (val[i] > val[i + 1]) {
                ull ans = val[i] - val[i + 1];
                cout << i << ' ' << ans << endl;
            } else {
                ull ans = val[i + 1] - val[i];
                cout << i + 1 << ' ' << ans << endl;
            }
            return;
        }
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
}