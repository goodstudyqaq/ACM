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
    string s;
    cin >> n >> s;

    int m = sqrt(n);
    if (m * m != n) {
        cout << "NO" << endl;
        return;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int idx = i * m + j;
            if (i == 0 || i == m - 1 || j == 0 || j == m - 1) {
                if (s[idx] == '0') {
                    cout << "NO" << endl;
                    return;
                }
            } else {
                if (s[idx] == '1') {
                    cout << "NO" << endl;
                    return;
                }
            }
        }
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
    return 0;
}