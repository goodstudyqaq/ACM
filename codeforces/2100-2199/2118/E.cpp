#include <bits/stdc++.h>

#include <cassert>

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
    int midx = (1 + n) / 2;
    int midy = (1 + m) / 2;

    int now = 1;
    int mx = max(n, m);

    // vector<vector<int>> mp(n + 1, vector<int>(m + 1, -1));

    auto draw = [&](int x, int y) {
        cout << x << ' ' << y << '\n';
        // int val1 = -1, val2 = -1;

        // for (int i = 1; i <= n; i++) {
        //     for (int j = 1; j <= m; j++) {
        //         if (mp[i][j] != -1) {
        //             int tmp1 = max(abs(x - i), abs(y - j));
        //             int tmp2 = abs(x - i) + abs(y - j);
        //             if (tmp1 > val1 || (tmp1 == val1 && tmp2 > val2)) {
        //                 val1 = tmp1;
        //                 val2 = tmp2;
        //             }
        //         }
        //     }
        // }

        // for (int i = 1; i <= n; i++) {
        //     for (int j = 1; j <= m; j++) {
        //         if (mp[i][j] != -1) {
        //             int tmp1 = max(abs(x - i), abs(y - j));
        //             int tmp2 = abs(x - i) + abs(y - j);
        //             if (tmp1 == val1 && tmp2 == val2) {
        //                 mp[i][j]++;
        //                 assert(mp[i][j] <= 3);
        //             }
        //         }
        //     }
        // }
        // mp[x][y] = 0;
    };
    draw(midx, midy);

    while (now < mx) {
        int lx = max(midx - now / 2, 1);
        int rx = min(midx + now / 2, n);

        int ly = max(midy - now / 2, 1);
        int ry = min(midy + now / 2, m);

        if (now < m) {
            // 先右边 1 个
            draw(midx, ry + 1);

            // 左边放 3 个
            draw(midx, ly - 1);

            for (int x = 1; midx + x <= rx; x++) {
                draw(midx - x, ly - 1);
                draw(midx + x, ly - 1);

                draw(midx - x, ry + 1);
                draw(midx + x, ry + 1);
            }
        }
        if (now < n) {
            draw(lx - 1, midy);
            draw(rx + 1, midy);

            for (int y = 1; midy + y <= ry; y++) {
                draw(lx - 1, midy - y);
                draw(lx - 1, midy + y);

                draw(rx + 1, midy - y);
                draw(rx + 1, midy + y);
            }
        }
        if (now < n && now < m) {
            draw(rx + 1, ry + 1);
            draw(rx + 1, ly - 1);
            draw(lx - 1, ly - 1);
            draw(lx - 1, ry + 1);
        }

        now += 2;
    }
    debug("zz");
    // debug(mp);
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