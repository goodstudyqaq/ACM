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
    vector<vector<char>> ans(2 * n, vector<char>(2 * n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char it;
            if ((i + j) % 2 == 0) {
                it = '#';

            } else {
                it = '.';
            }
            ans[i * 2][j * 2] = it;
            ans[i * 2][j * 2 + 1] = it;
            ans[i * 2 + 1][j * 2] = it;
            ans[i * 2 + 1][j * 2 + 1] = it;
        }
    }
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            cout << ans[i][j];
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