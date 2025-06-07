#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int h, w;
    cin >> h >> w;

    vector<vector<long long>> a(h, vector<long long>(w));
    vector<vector<long long>> vis(h, vector<long long>(w));

    long long res = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> a[i][j];
            res ^= a[i][j];
        }
    }

    long long ans = 0;
    function<void(int x, int y, long long &)> dfs = [&](int x, int y, long long &now) {
        // debug(x, y, now);
        if (x == h) {
            long long tmp = res ^ now;
            ans = max(ans, tmp);
            return;
        }
        if (vis[x][y]) {
            if (y + 1 == w) {
                dfs(x + 1, 0, now);
            } else {
                dfs(x, y + 1, now);
            }
            return;
        }

        // 竖着放
        if (x + 1 < h) {
            vis[x][y] = 1;
            vis[x + 1][y] = 1;

            now ^= a[x][y];
            now ^= a[x + 1][y];

            if (y + 1 == w) {
                dfs(x + 1, 0, now);
            } else {
                dfs(x, y + 1, now);
            }
            vis[x][y] = 0;
            vis[x + 1][y] = 0;

            now ^= a[x][y];
            now ^= a[x + 1][y];
        }

        // 横着放
        if (y + 1 < w && vis[x][y + 1] == 0) {
            vis[x][y] = 1;
            vis[x][y + 1] = 1;
            now ^= a[x][y];
            now ^= a[x][y + 1];

            dfs(x, y + 1, now);
            vis[x][y] = 0;
            vis[x][y + 1] = 0;
            now ^= a[x][y];
            now ^= a[x][y + 1];
        }

        // 不放
        if (y + 1 == w) {
            dfs(x + 1, 0, now);
        } else {
            dfs(x, y + 1, now);
        }
    };

    long long now = 0;
    dfs(0, 0, now);
    cout << ans << '\n';
}