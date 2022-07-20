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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    const int inf = numeric_limits<int>::max() / 2;
    vector<int> next(a[0] + 1, 0);

    for (int i = 0; i < n; i++) {
        int last = inf;
        for (int j = 1; j <= min(k, a[i]); j = a[i] / (a[i] / j) + 1) {
            int val = a[i] / j;
            if (val + 1 <= a[0]) {
                next[val + 1] = max(next[val + 1], last);
            }
            last = val;
        }
        next[0] = max(next[0], last);
    }

    int now = 0;
    int ans = inf;
    for (int i = 0; i <= a[0]; i++) {
        now = max(now, next[i]);
        ans = min(ans, now - i);
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
}