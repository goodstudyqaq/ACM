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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    int d[8][2] = {1, 0, -1, 0, 0, -1, 0, 1, 1, 1, 1, -1, -1, 1, -1, -1};

    auto in = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    auto can = [&](int x, int y) {
        if (in(x, y) == 0) return false;
        for (int i = 0; i < 4; i++) {
            int x2 = x + d[i][0], y2 = y + d[i][1];
            if (in(x2, y2) && s[x2][y2] == '#') return false;
        }
        return true;
    };

    const int inf = numeric_limits<int>::max() / 2;
    vector<vector<int>> dis(n, vector<int>(m, inf));
    deque<pii> Q;
    for (int i = 0; i < n; i++) {
        if (s[i][0] == '#') {
            dis[i][0] = 0;
            Q.push_front({i, 0});
        } else if (can(i, 0)) {
            dis[i][0] = 1;
            Q.push_back({i, 0});
        }
    }

    vector<vector<int>> idx(n, vector<int>(m, 0));
    while (!Q.empty()) {
        auto [x, y] = Q.front();
        Q.pop_front();

        for (int i = 4; i < 8; i++) {
            int x2 = x + d[i][0], y2 = y + d[i][1];
            if (can(x2, y2) == 0) continue;
            int w = (s[x2][y2] != '#');
            if (dis[x2][y2] > dis[x][y] + w) {
                dis[x2][y2] = dis[x][y] + w;
                idx[x2][y2] = i;
                if (w) {
                    Q.push_back({x2, y2});
                } else {
                    Q.push_front({x2, y2});
                }
            }
        }
    }

    int x = 0, y = m - 1;
    for (int i = 0; i < n; i++) {
        if (dis[i][m - 1] < dis[x][m - 1]) {
            x = i;
        }
    }

    if (dis[x][y] == inf) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;

    while (true) {
        s[x][y] = '#';
        if (y == 0) break;
        int the_idx = idx[x][y];
        x -= d[the_idx][0];
        y -= d[the_idx][1];
    }

    for (int i = 0; i < n; i++) {
        cout << s[i] << endl;
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
}