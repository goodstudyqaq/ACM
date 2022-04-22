#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
    vector v = vector(2, vector(2, 0));
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        v[i % 2][a % 2] = 1;
    }

    if (v[0][0] && v[0][1]) {
        cout << "NO" << endl;
        return;
    }
    if (v[1][0] && v[1][1]) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
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