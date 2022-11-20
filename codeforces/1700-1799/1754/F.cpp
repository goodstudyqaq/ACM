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
    int n, m, p, q;
    cin >> n >> m >> p >> q;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    const ll inf = numeric_limits<ll>::max() / 2;

    auto work = [&](vector<vector<ll>> &dis, int f) {
        dis = vector(n, vector(m, inf));
        int d[8][2] = {2, 0, -2, 0, 0, 2, 0, -2, 1, 1, 1, -1, -1, -1, -1, 1};

        int d2[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
        string s_d2[4] = {"UD", "DU", "LR", "RL"};

        // 顺时针转
        int d3[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
        string s_d3[4] = {"UD", "RL", "DU", "LR"};

        // 逆时针转
        int d4[4][2] = {1, 0, 0, -1, -1, 0, 0, 1};
        string s_d4[4] = {"LR", "UD", "RL", "DU"};

        typedef pair<ll, pii> plii;

        priority_queue<plii, vector<plii>, greater<plii>> Q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if ((i + j) % 2 != f) continue;
                if (s[i][j] == '.') {
                    dis[i][j] = 0;
                    Q.push({0, {i, j}});
                }
            }
        }
        vector vis = vector(n, vector(m, 0));

        auto in = [&](int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < m;
        };

        auto ok = [&](int x, int y, int idx) {
            int x2 = x + d[idx][0];
            int y2 = y + d[idx][1];

            if (in(x, y) == 0 || in(x2, y2) == 0) return false;
            if (idx < 4) {
                int x3 = x + d2[idx][0], y3 = y + d2[idx][1];
                string tmp = string("") + s[x3][y3] + s[x2][y2];
                return tmp == s_d2[idx];
            } else {
                idx -= 4;
                int x3 = x + d3[idx][0], y3 = y + d3[idx][1];
                string tmp = string("") + s[x3][y3] + s[x2][y2];
                if (tmp == s_d3[idx]) return true;
                x3 = x + d4[idx][0], y3 = y + d4[idx][1];
                tmp = string("") + s[x3][y3] + s[x2][y2];
                return tmp == s_d4[idx];
            }
        };
        debug(f);

        while (!Q.empty()) {
            auto it = Q.top();
            Q.pop();
            ll the_dis = it.first;
            auto [x, y] = it.second;
            debug(the_dis, x, y);
            if (vis[x][y]) continue;
            vis[x][y] = 1;

            for (int i = 0; i < 8; i++) {
                if (ok(x, y, i) == 0) continue;
                int x2 = x + d[i][0], y2 = y + d[i][1];
                ll ct = (i < 4 ? q : p);
                if (dis[x2][y2] > dis[x][y] + ct) {
                    dis[x2][y2] = dis[x][y] + ct;
                    Q.push({dis[x2][y2], {x2, y2}});
                }
            }
        }
    };

    vector<vector<ll>> d[2];

    work(d[0], 0);
    work(d[1], 1);

    ll res = inf;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int f = (i + j) % 2;
            ll ct1 = (i + 1 < n ? d[f][i][j] + d[f ^ 1][i + 1][j] : inf);
            ll ct2 = (j + 1 < m ? d[f][i][j] + d[f ^ 1][i][j + 1] : inf);
            ll ct = min(ct1, ct2);
            res = min(res, ct);
        }
    }
    // debug(d[0]);
    // debug(d[1]);
    debug(inf);
    if (res == inf) {
        res = -1;
    }
    cout << res << endl;
    return 0;
}