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
typedef array<int, 2> a2;

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

    int l = -1, r = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0 && l == -1) {
            l = i;
        }
        if (a[i] == 0) {
            r = i;
        }
    }

    if (l == 0 && r == n - 1) {
        cout << "Bob\n";
    } else {
        cout << "Alice\n";
    }
    // if (l == -1 && r == -1) {
    //     cout << "Alice\n";
    //     return;
    // }

    // if (l == 0 || r == n - 1) {
    //     cout << "Alice\n";
    // } else {
    //     cout << "Bob\n";
    // }
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