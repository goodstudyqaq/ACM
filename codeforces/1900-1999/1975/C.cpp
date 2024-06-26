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
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int mx = 0;
    // 2
    for (int i = 1; i < n; i++) {
        mx = max(mx, min(a[i], a[i + 1]));
    }
    // 3
    for (int i = 1; i <= n - 2; i++) {
        vector<int> v{a[i], a[i + 1], a[i + 2]};
        sort(v.begin(), v.end());
        mx = max(mx, v[1]);
    }
    cout << mx << endl;
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