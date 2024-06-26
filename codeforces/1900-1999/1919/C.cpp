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
    int ans = 0;
    int x = a[1], y = -1;
    for (int i = 2; i <= n; i++) {
        bool f1 = x < a[i];
        bool f2 = (y != -1 && y < a[i]);
        if (f1 == f2) {
            if (f1) {
                ans++;
            }
            if (y == -1 || x < y) {
                x = a[i];
            } else {
                y = a[i];
            }
        } else {
            if (!f1) {
                x = a[i];
            } else {
                y = a[i];
            }
        }
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