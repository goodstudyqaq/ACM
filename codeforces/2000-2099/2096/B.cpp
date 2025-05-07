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
    vector<long long> l(n + 1), r(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> l[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }

    long long ans = 0;
    vector<long long> v;
    for (int i = 1; i <= n; i++) {
        if (l[i] > r[i]) {
            ans += l[i];
            v.push_back(r[i]);
        } else {
            ans += r[i];
            v.push_back(l[i]);
        }
    }
    debug(ans);
    sort(v.begin(), v.end());
    debug(v);
    for (int i = n - 1; i > n - k; i--) {
        ans += v[i];
    }
    cout << ans + 1 << '\n';
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