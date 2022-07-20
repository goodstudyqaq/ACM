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

    int n, m;
    cin >> n >> m;
    vector V = vector(n, vector(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> V[i][j];
        }
    }

    int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};

    auto check = [&](int x, int y) {
        if (V[x][y] == 1) return true;
        for (int i = 0; i < 4; i++) {
            int x2 = x + d[i][0], y2 = y + d[i][1];
            if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m && V[x2][y2] < V[x][y]) {
                return true;
            }
        }
        return false;
    };

    vector<pii> bad;
    vector vis = vector(n, vector(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!check(i, j)) {
                bad.push_back({i, j});
                vis[i][j] = 1;
            }
        }
    }

    if (bad.size() > 5) {
        cout << 2 << endl;
        return 0;
    } else if (bad.size() == 0) {
        cout << 0 << endl;
        return 0;
    }

    pii choose = bad[0];

    int cnt = 0;

    auto check2 = [&](int x1, int y1, int x2, int y2) -> bool {
        swap(V[x1][y1], V[x2][y2]);
        bool flag = true;
        flag &= check(x1, y1);
        flag &= check(x2, y2);
        for (int i = 0; i < 4; i++) {
            int x3 = x1 + d[i][0], y3 = y1 + d[i][1];
            if (x3 >= 0 && x3 < n && y3 >= 0 && y3 < m) {
                flag &= check(x3, y3);
            }
            int x4 = x2 + d[i][0], y4 = y2 + d[i][1];
            if (x4 >= 0 && x4 < n && y4 >= 0 && y4 < m) {
                flag &= check(x4, y4);
            }
        }

        for (auto it : bad) {
            flag &= check(it.first, it.second);
        }

        swap(V[x1][y1], V[x2][y2]);
        if (flag) {
            debug(x1, y1, x2, y2);
        }
        return flag;
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // 拿(i, j) 和 (x, y) 换 条件：V[i][j] > V[x][y] && vis[i][j] = 0
            if (V[i][j] > V[choose.first][choose.second] && !vis[i][j]) {
                bool flag = check2(i, j, choose.first, choose.second);
                if (flag) {
                    cnt++;
                }
            }

            // 拿(i, j) 和 (x, y) 周围去换 条件：V[i][j] < V[x][y]
            if (V[i][j] < V[choose.first][choose.second]) {
                for (int k = 0; k < 4; k++) {
                    int x2 = choose.first + d[k][0], y2 = choose.second + d[k][1];
                    if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m) {
                        bool flag = check2(i, j, x2, y2);
                        if (flag) cnt++;
                    }
                }
            }
        }
    }

    if (cnt) {
        cout << 1 << ' ' << cnt << endl;
    } else {
        cout << 2 << endl;
    }
    return 0;
}