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
    vector<int> b(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> b[i];
    }
    vector<int> a(n);

    for (int i = 1; i < n; i++) {
        if (i == n - 1)
            a[i] = b[i - 1];
        else {
            a[i] = b[i - 1] | b[i];
        }
    }

    a[0] = b[0];
    for (int i = 0; i < n - 1; i++) {
        if ((a[i] & a[i + 1]) != b[i]) {
            cout << -1 << endl;
            return;
        }
    }
    for (int i = 0; i < n; i++) {
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
    return 0;
}