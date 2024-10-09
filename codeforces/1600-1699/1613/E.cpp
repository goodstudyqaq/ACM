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

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    auto work = [&](int x, int y) {
        int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
        auto check = [&](int x, int y) {
            int res = 0;
            for (int i = 0; i < 4; i++) {
                int x2 = x + d[i][0], y2 = y + d[i][1];
                if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m && s[x2][y2] == '.') {
                    res++;
                }
            }
            return res <= 1;
        };

        vector<vector<int>> vis(n, vector<int>(m));
        queue<array<int, 2>> Q;
        Q.push({x, y});
        vis[x][y] = 1;
        while (!Q.empty()) {
            auto [x, y] = Q.front();
            Q.pop();
            for (int i = 0; i < 4; i++) {
                int x2 = x + d[i][0], y2 = y + d[i][1];
                if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m && vis[x2][y2] == 0 && s[x2][y2] == '.' && check(x2, y2)) {
                    vis[x2][y2] = 1;
                    s[x2][y2] = '+';
                    Q.push({x2, y2});
                }
            }
        }
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'L') {
                work(i, j);
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << s[i] << '\n';
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