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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<vector<pii>> a(2, vector<pii>(n));

    // 0 向上，1 向右
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> a[j][i].first >> a[j][i].second;
        }
    }

    auto get_dis = [&](pii x, pii y, bool f) -> ll {
        if (f == 0) {
            x.first++;
        } else {
            x.second++;
        }
        return 1LL * abs(x.first - y.first) + 1LL * abs(x.second - y.second) + 1;
    };

    vector<vector<vector<ll>>> d = vector(20, vector(4, vector(n, 0LL)));

    for (int i = 1; i < n - 1; i++) {
        for (int j = 0; j < 4; j++) {
            int x = j & 1, y = (j >> 1) & 1;
            d[0][j][i] = get_dis(a[x][i], a[y][i + 1], x);
        }
    }
    const ll inf = numeric_limits<ll>::max() / 2;

    for (int j = 1; j < 20; j++) {
        for (int i = 1; i < n; i++) {
            int go = i + (1 << j);
            if (go > n - 1) break;
            for (int k = 0; k < 4; k++) {
                // d[j][k][i]
                int x = k & 1, y = (k >> 1) & 1;
                int go2 = i + (1 << (j - 1));
                ll tmp_res = inf;
                for (int k2 = 0; k2 < 2; k2++) {
                    int s1 = x + k2 * 2;
                    int s2 = k2 + y * 2;
                    tmp_res = min(tmp_res, d[j - 1][s1][i] + d[j - 1][s2][go2]);
                }
                d[j][k][i] = tmp_res;
            }
        }
    }

    auto query = [&](int x1, int y1, int x2, int y2) -> ll {
        int d1 = max(x1, y1);
        int d2 = max(x2, y2);

        if (d1 > d2) {
            swap(x1, x2);
            swap(y1, y2);
            swap(d1, d2);
        }

        if (d1 == d2) {
            return abs(x1 - x2) + abs(y1 - y2);
        }

        // d1 -> d2 - 1
        int dest = d2 - 1;

        vector<ll> now_dis = {0, inf, inf, 0};

        int now_d = d1;

        for (int i = 19; i >= 0; i--) {
            int go = now_d + (1 << i);
            if (go > dest) continue;
            vector<ll> new_dis = {inf, inf, inf, inf};

            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int k2 = 0; k2 < 2; k2++) {
                        int s1 = j + k * 2;
                        int s2 = k + k2 * 2;
                        int s3 = j + k2 * 2;
                        new_dis[s3] = min(new_dis[s3], now_dis[s1] + d[i][s2][now_d]);
                    }
                }
            }
            now_dis = new_dis;
            now_d = go;
        }

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                ll dis = abs(x1 - a[i][d1].first) + abs(y1 - a[i][d1].second) + get_dis(a[j][dest], {x2, y2}, j);
                now_dis[i + 2 * j] += dis;
            }
        }
        ll res = *min_element(now_dis.begin(), now_dis.end());
        return res;
    };

    int m;
    cin >> m;
    while (m--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        cout << query(x1, y1, x2, y2) << endl;
    }
    return 0;
}