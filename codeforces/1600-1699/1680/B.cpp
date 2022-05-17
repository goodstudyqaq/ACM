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
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    int x = -1, y = -1;
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (s[i][j] == 'R') {
                x = i, y = j;
                j = m + 1;
                break;
            }
        }
    }
    debug(x, y);
    if (x == -1) {
        cout << "NO" << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'R') {
                if (i < x || j < y) {
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
}