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

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

void solve() {
    int n;
    cin >> n;

    const long long inf = numeric_limits<long long>::max();
    long long mi_x = inf;
    long long mi_y = inf;

    long long mx_y = -inf;
    long long mx_x = -inf;

    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        mi_x = min(mi_x, x[i]);
        mi_y = min(mi_y, y[i]);
        mx_y = max(mx_y, y[i]);
        mx_x = max(mx_x, x[i]);
    }

    auto get_d = [&](long long x1, long long y1, long long x2, long long y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    };

    // mi_x, mi_y 作为原点
    int o_idx = 0;
    for (int i = 0; i < n; i++) {
        long long d1 = get_d(mi_x, mi_y, x[i], y[i]);
        long long d2 = get_d(mi_x, mi_y, x[o_idx], y[o_idx]);
        if (d1 < d2) {
            o_idx = i;
        }
    }
    map<int, char> M = {{0, 'U'}, {1, 'R'}, {2, 'D'}, {3, 'L'}};
    vector<pii> op;
    auto move = [&](int d, int k) {
        op.push_back({d, k});
        cout << "? " << M[d] << ' ' << k << '\n';
        fflush(stdout);
        long long ans;
        cin >> ans;
        return ans;
    };

    long long tmp_mx_x = 1e9;
    const long long mx_move = 1e9;
    long long res;
    while (tmp_mx_x > mi_x) {
        long long dis = min(mx_move, tmp_mx_x - mi_x);
        res = move(3, dis);
        tmp_mx_x -= dis;
    }

    long long tmp_mx_y = 1e9;
    while (tmp_mx_y > mi_y) {
        long long dis = min(mx_move, tmp_mx_y - mi_y);
        res = move(2, dis);
        tmp_mx_y -= dis;
    }

    int d[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
    auto out = [&](long long x, long long y) {
        for (auto it : op) {
            int dir = (it.first + 2) % 4;
            x = x + d[dir][0] * it.second;
            y = y + d[dir][1] * it.second;
        }

        cout << "! " << x << ' ' << y << '\n';
        fflush(stdout);
    };

    // res 是到 o_idx 的距离
    if (res == 0) {
        out(x[o_idx], y[o_idx]);
        return;
    }

    if (n == 1) {
        long long res2;
        while (res) {
            long long dis = min(mx_move, res);
            res2 = move(0, dis);
            res -= dis;
        }

        assert(res2 % 2 == 0);

        long long tmp = res2 / 2;
        debug(res2);

        long long now_x = x[o_idx] - tmp, now_y = y[o_idx] + tmp;
        out(now_x, now_y);
    } else {
        long long res2;

        // mi_x, mx_y 作为原点
        int o_idx2 = 0;
        for (int i = 0; i < n; i++) {
            long long d1 = get_d(mi_x, mx_y, x[i], y[i]);
            long long d2 = get_d(mi_x, mx_y, x[o_idx2], y[o_idx2]);
            if (d1 < d2) {
                o_idx2 = i;
            }
        }
        debug(x[o_idx2], y[o_idx2]);

        tmp_mx_y = -3e9;
        while (tmp_mx_y < mx_y) {
            long long dis = min(mx_move, mx_y - tmp_mx_y);
            res2 = move(0, dis);
            tmp_mx_y += dis;
        }
        long long x1 = x[o_idx], y1 = y[o_idx];
        long long x2 = x[o_idx2], y2 = y[o_idx2];
        long long nowx = (x1 + y1 + x2 + mx_y + 3e9 - y2 - res - res2) / 2;
        long long nowy = x1 - nowx + y1 - res;
        nowy += 3e9 + mx_y;
        // nowy -= (mx_y  1e9);
        out(nowx, nowy);
    }
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}