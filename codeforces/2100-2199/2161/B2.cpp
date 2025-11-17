#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
char g[105][105];
bool vis[105][105];
int sx, sy;
vector<pair<int, int>> p;
bool ok;

void check_1 (int allow_d) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            vis[i][j] = false;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int dx = i - sx;
            int dy = j - sy;
            int D = dy - dx;
            if (D == 0 || D == allow_d) {
                vis[i][j] = true;
            }
        }
    }

    /*for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << vis[i][j];
        }
        cout << endl;
    }*/
    bool mb = true;
    for (auto [x, y] : p) {
        if (vis[x][y]) {
            continue;
        }
        mb = false;
    }
    if (mb) {
        ok = true;
    }
    //cout << "mb=" << mb << endl;
}

void check_2 (int allow_d) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            vis[i][j] = false;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int dx = - (i - sx);
            int dy = j - sy;
            int D = dy - dx;
            if (D == 0 || D == allow_d) {
                vis[i][j] = true;
            }
        }
    }

    /*for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << vis[i][j];
        }
        cout << endl;
    }*/
    bool mb = true;
    for (auto [x, y] : p) {
        if (vis[x][y]) {
            continue;
        }
        mb = false;
    }
    if (mb) {
        ok = true;
    }
    //cout << "mb=" << mb << endl;
}

void solve() {
    //cout << "---" << endl;
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf ("%s", g[i] + 1);
    }
    p.clear();
    bool zfx = false;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (g[i][j] == '#') {
                p.push_back ({i, j});
                if (i + 1 <= n && j + 1 <= n && g[i][j] == '#' && g[i + 1][j] == '#' && g[i][j + 1] == '#' && g[i + 1][j + 1] == '#' ) {
                    zfx = true;
                }
            }
        }
    }
    if (p.empty() ) {
        puts ("YES");
        return;
    }
    // 判断正方形特例
    if (zfx) {
        if (p.size() == 4) {
            puts ("YES");
            return;
        }
        puts ("NO");
        return;
    }

    /*ok = true;
    for (auto [x, y] : p) {
        for (auto [vx, vy] : p) {
            int dx = abs (vx - x);
            int dy = abs (vy - y);
            if (abs (dx - dy) > 1) {
                ok = false;
                break;
            }
        }
    }
    if (!ok) {
        puts ("NO");
        return;
    }*/

    // cout << "?" << endl;
    ok = false;

    // 对第一个点，枚举主对角线
    sx = p[0].first;
    sy = p[0].second;

    check_1 (-1);
    if (ok) {
        puts ("YES");
        return;
    }
    check_1 (1);
    if (ok) {
        puts ("YES");
        return;
    }
    check_2 (-1);
    if (ok) {
        puts ("YES");
        return;
    }
    check_2 (1);
    if (ok) {
        puts ("YES");
        return;
    }

    puts ("NO");
    return;

}

int main() {
#ifdef LOCAL
    freopen ("A.in", "r", stdin);
    freopen ("A.out", "w", stdout);
#endif // LOCAL
    int T;
    scanf ("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}