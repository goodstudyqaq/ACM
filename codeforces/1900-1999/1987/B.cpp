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
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        if (a[i] < mx) {
            cnt[mx - a[i]]++;
        }
        mx = max(mx, a[i]);
    }
    debug(cnt);

    int Sz = 0;
    for (auto it : cnt) {
        Sz += it.second;
    }

    long long ans = 0;
    int use = 0;
    int sz = 0;

    for (auto it : cnt) {
        int times = it.first - use;
        ans += 1LL * times * (Sz - sz + 1);
        use = it.first;
        sz += it.second;
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