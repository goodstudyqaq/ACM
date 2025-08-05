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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    auto work = [&](int f) {
        int x = 0, y = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] > a[x][y]) {
                    x = i, y = j;
                }
            }
        }

        if (f == 0) {
            for (int i = 0; i < m; i++) {
                a[x][i]--;
            }
            return x;
        } else {
            for (int i = 0; i < n; i++) {
                a[i][y]--;
            }
            return y;
        }
    };

    int ans = 1e9;

    auto get_mx = [&]() {
        int mx = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                mx = max(mx, a[i][j]);
            }
        }
        return mx;
    };

    for (int i = 0; i < 2; i++) {
        auto backup = a;
        int x = work(i);
        int y = work(i ^ 1);
        if (i == 0) {
            a[x][y]++;
        } else {
            a[y][x]++;
        }
        ans = min(ans, get_mx());
        a = backup;
    }
    cout << ans << '\n';
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