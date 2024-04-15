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
    if (n == 1) {
        cout << 1 << ' ' << 1 << endl;
        cout << 1 << ' ' << 1 << ' ' << 1 << endl;
        return;
    }

    long long ans = 0;

    int num = 1;
    for (int i = 1; i <= n; i++) {
        ans += 1LL * num * i;
        num += 2;
    }

    long long step = 2 * n;
    cout << ans << ' ' << step << endl;

    for (int i = n; i >= 1; i--) {
        cout << 1 << ' ' << i << ' ';
        for (int k = 1; k <= n; k++) {
            cout << k << ' ';
        }
        cout << endl;
        cout << 2 << ' ' << i << ' ';
        for (int k = 1; k <= n; k++) {
            cout << k << ' ';
        }
        cout << endl;
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
    return 0;
}