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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int mx = 0, cnt = 0;
    for (int i = 0; i < n; i += 2) {
        cnt++;
        mx = max(mx, a[i]);
    }
    int ans = mx + cnt;

    mx = 0, cnt = 0;
    for (int i = 1; i < n; i += 2) {
        cnt++;
        mx = max(mx, a[i]);
    }
    ans = max(ans, mx + cnt);
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