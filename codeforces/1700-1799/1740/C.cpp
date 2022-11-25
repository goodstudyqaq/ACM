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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    set<int> S;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a.begin() + 1, a.begin() + 1 + n);
    int a_cnt = unique(a.begin() + 1, a.begin() + 1 + n) - a.begin() - 1;

    if (a_cnt == 1) {
        cout << 0 << endl;
    } else if (a_cnt == 2) {
        cout << 2 * (a[2] - a[1]) << endl;
    } else {
        int ans = 0;
        for (int i = 1; i <= n - 2; i++) {
            ans = max(ans, a[n] - a[i] + a[i + 1] - a[i]);
        }

        for (int i = n; i >= 2; i--) {
            ans = max(ans, a[i] - a[1] + a[i] - a[i - 1]);
        }

        cout << ans << endl;
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