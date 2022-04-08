#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

double dp[205][2];
double res[2][130000 + 10];

const double eps = 1e-8;

int sgn(double v) {
    if (fabs(v) < eps) return 0;
    if (v > 0) return 1;
    return -1;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int hp, dt, l, r, p;
    int hp2, dt2, l2, r2, p2;
    cin >> hp >> dt >> l >> r >> p;
    cin >> hp2 >> dt2 >> l2 >> r2 >> p2;

    if (p == 100) {
        cout << 0 << endl;
        return 0;
    }
    if (p2 == 100) {
        cout << 1 << endl;
        return 0;
    }

    int Len = max(r - l + 1, r2 - l2 + 1);
    int maxn = 201, maxm = min(123500, 100000000 / max(hp, hp2) / Len);
    debug(maxn, maxm);
    auto work = [&](int hp, int dt, int l, int r, int p, int aim, int f) -> void {
        double _p = 1.0 * p / 100;
        double _p2 = 1.0 / (r - l + 1);

        for (int i = 0; i <= maxn; i++) {
            for (int j = 0; j < 2; j++) {
                dp[i][j] = 0;
            }
        }

        dp[0][0] = 1.0;
        for (int j = 0; j < maxm - 1; j++) {
            int flag = j % 2;
            for (int i = 0; i <= maxn; i++) {
                dp[i][flag ^ 1] = 0;
            }
            for (int i = 0; i < aim; i++) {
                if (sgn(dp[i][flag]) == 0) continue;
                // dp[i][j] 用 j 次打了 i 次血的概率
                // 没命中
                dp[i][flag ^ 1] += _p * dp[i][flag];
                double tmp_p = 1.0 - _p;
                // 命中
                for (int k = l; k <= r; k++) {
                    int tmp = min(i + k, maxn - 1);
                    double tmp1 = tmp_p * _p2 * dp[i][flag];
                    dp[tmp][flag ^ 1] += tmp1;
                    if (tmp >= aim) {
                        res[f][j + 1] += tmp1;
                    }
                }
            }
        }
        // for (int i = aim; i < maxn; i++) {
        //     for (int j = 0; j < maxm; j++) {
        //         res[j] += dp[i][j];
        //     }
        // }
    };

    work(hp, dt, l, r, p, hp2, 0);
    work(hp2, dt2, l2, r2, p2, hp, 1);

    for (int i = 1; i < maxm; i++) {
        res[1][i] += res[1][i - 1];
        res[1][i] = min(res[1][i], 1.0);
    }
    double ans = 0;
    for (int i = 1; i < maxm; i++) {
        double tmp = res[0][i];
        if (tmp == 0) continue;
        int time_ct = (i - 1) * dt + dt2 - 1;
        int times = time_ct / dt2;
        if (times >= maxm) break;
        if (res[1][times] == 1) break;
        // debug(i, times, tmp, dp2[times]);
        ans += tmp * (1.0 - res[1][times]);
        if (tmp == 1) break;
    }
    cout << ans << endl;
    return 0;
}