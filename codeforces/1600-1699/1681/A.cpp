#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        mx = max(mx, a);
    }

    int m;
    cin >> m;
    int mx2 = 0;
    for (int i = 0; i < m; i++) {
        int b;
        cin >> b;
        mx2 = max(mx2, b);
    }

    if (mx >= mx2) {
        cout << "Alice" << endl;
    } else {
        cout << "Bob" << endl;
    }

    if (mx2 >= mx) {
        cout << "Bob" << endl;
    } else {
        cout << "Alice" << endl;
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
}