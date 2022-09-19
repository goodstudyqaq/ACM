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
    vector<vector<ll>> c = vector(2 * n, vector(2 * n, 0LL));
    ll ans = 0;
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            cin >> c[i][j];
            if (i >= n && j >= n) {
                ans += c[i][j];
                c[i][j] = 0;
            }
        }
    }

    ll ct2 = min({c[0][n], c[0][2 * n - 1], c[n - 1][n], c[n - 1][2 * n - 1], c[2 * n - 1][0], c[2 * n - 1][n - 1], c[n][0], c[n][n - 1]});
    cout << ct2 + ans << endl;
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