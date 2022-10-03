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
    vector<int> d(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    vector<int> a(n + 1);
    a[1] = d[1];

    for (int i = 2; i <= n; i++) {
        int _d = d[i];
        if (_d == 0) {
            a[i] = a[i - 1];
            continue;
        }

        if (a[i - 1] >= _d) {
            cout << -1 << endl;
            return;
        }
        a[i] = a[i - 1] + _d;
    }
    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
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