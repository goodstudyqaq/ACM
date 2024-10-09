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

template <class T>
struct CumulativeSum2D {
    vector<vector<T>> data;

    CumulativeSum2D(int W, int H) : data(W + 1, vector<T>(H + 1, 0)) {}

    void add(int x, int y, T z) {
        ++x, ++y;
        if (x >= data.size() || y >= data[0].size()) return;
        data[x][y] += z;
    }

    void build() {
        for (int i = 1; i < data.size(); i++) {
            for (int j = 1; j < data[i].size(); j++) {
                data[i][j] += data[i][j - 1] + data[i - 1][j] - data[i - 1][j - 1];
            }
        }
    }

    T query(int sx, int sy, int gx, int gy) const {
        gx++, gy++;
        return (data[gx][gy] - data[sx][gy] - data[gx][sy] + data[sx][sy]);
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> ss(n);
    for (int i = 0; i < n; i++) {
        cin >> ss[i];
    }
    int res = 0;
    for (int t = 0; t < 4; t++) {
        debug(t);
        vector<vector<int>> sum(n, vector<int>(m));

        vector<string> s;
        if (t == 0 || t == 3) {
            s = ss;
        }
        if (t == 1 || t == 2) {
            s = ss;
            for (int i = 0; i < n / 2; i++) {
                swap(s[i], s[n - i - 1]);
            }
        }

        if (t == 2 || t == 3) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m / 2; j++) {
                    swap(s[i][j], s[i][m - j - 1]);
                }
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < m; j++) {
                sum[i][j] += (s[i][j] == '#');
                if (i + 1 < n && j + 1 < m) {
                    sum[i][j] += sum[i + 1][j + 1];
                }
            }
        }
        CumulativeSum2D<int> sum2d(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                sum2d.add(i, j, sum[i][j]);
            }
        }
        sum2d.build();

        auto work = [&](int x, int y) -> int {
            int upx = x - k;
            int res = 0;
            if (upx >= 0) {
                res += sum2d.query(upx, y, x, y);
            } else {
                res += sum2d.query(0, y, x, y);
                int tmp = k - x;
                res += sum2d.query(0, y + 1, 0, min(y + tmp, m - 1));
            }

            int res2 = 0;
            if (x + 1 < n && y + 1 < m) {
                res2 = sum2d.query(x + 1, y + 1, x + 1, min(y + k + 1, m - 1));
            }
            // debug(x, y, res, res2, res - res2);
            return res - res2;
        };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res = max(res, work(i, j));
            }
        }
    }
    cout << res << endl;
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