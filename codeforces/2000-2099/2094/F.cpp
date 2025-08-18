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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> ans(n, vector<int>(m));
    if (n % k == 0 && m % k == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i][j] = (i + j) % k + 1;
            }
        }
    } else {
        if (n % k != 0) {
            int now = 0;
            for (int j = 0; j < m; j++) {
                for (int i = 0; i < n; i++) {
                    ans[i][j] = now + 1;
                    now++;
                    now %= k;
                }
            }
        } else {
            int now = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    ans[i][j] = now + 1;
                    now++;
                    now %= k;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
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