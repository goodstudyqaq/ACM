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
    bool eq = true;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i != 1 && a[i] != a[i - 1]) eq = false;
    }
    int same = a[1];
    if (eq) {
        cout << -1 << endl;
        return;
    }



    int now = 1;
    int ans = 1e9;
    while (now <= n) {
        int go = now;
        while (go <= n && a[go] == a[now]) go++;
        ans = min(ans, go - now);
        now = go + 1;
    }
    if (ans == 1e9) {
        ans = -1;
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