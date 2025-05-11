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

    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    typedef pair<int, int> pii;
    queue<pii> Q;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'E') {
                Q.push({i, j});
            }
        }
    }
    int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};

    string go = "v^><";

    while (!Q.empty()) {
        auto [x, y] = Q.front();
        // debug(x, y);
        Q.pop();
        for (int i = 0; i < 4; i++) {
            int x2 = x + d[i][0], y2 = y + d[i][1];
            if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m && s[x2][y2] == '.') {
                Q.push({x2, y2});
                s[x2][y2] = go[i];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << s[i] << '\n';
    }
}