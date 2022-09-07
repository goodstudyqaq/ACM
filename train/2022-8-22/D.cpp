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
typedef array<int, 3> a3;

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
    vector a = vector(n, vector(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    auto check2 = [&](int x, int y) {
        if (x < 0 || x >= n || y < 0 || y >= m) return false;
        return true;
    };

    auto check = [&](int x, int y) -> pair<bool, int> {
        set<int> S;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                int _x = x + i, _y = y + j;
                if (check2(_x, _y)) {
                    S.insert(a[_x][_y]);
                } else {
                    return {false, -1};
                }
            }
        }
        if (S.size() == 1) {
            if (*S.begin() == -1) return {false, -1};
            return {true, *S.begin()};
        }
        if (S.size() == 2 && *S.begin() == -1) return {true, *next(S.begin())};
        return {false, -1};
    };

    auto work = [&](int x, int y) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                a[x + i][y + j] = -1;
            }
        }
    };

    vector<a3> ans;
    queue<pii> Q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            auto it = check(i, j);
            if (it.first) {
                Q.push({i, j});
                ans.push_back({i, j, it.second});
                work(i, j);
            }
        }
    }

    while (!Q.empty()) {
        auto [x, y] = Q.front();
        debug(x, y);
        Q.pop();

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                auto it = check(x + i, y + j);
                if (it.first) {
                    Q.push({x + i, y + j});
                    ans.push_back({x + i, y + j, it.second});
                    work(x + i, y + j);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] != -1) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    vector b = vector(n, vector(m, 0));
    for (auto it : ans) {
        cout << it[0] + 1 << ' ' << it[1] + 1 << ' ' << it[2] << endl;
        // int x = it[0], y = it[1], c = it[2];
        // for (int i = 0; i < 2; i++) {
        //     for (int j = 0; j < 2; j++) {
        //         b[x + i][y + j] = c;
        //     }
        // }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         cout << b[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    return 0;
}