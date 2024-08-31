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
        return (data[gx][gy] - data[sx][gy] - data[gx][sy] + data[sx][sy]);
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<long long>> mp(n, vector<long long>(m));
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mp[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<vector<int>> data(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            data[i][j] = s[i][j] - '0' ? 1 : -1;
        }
    }

    CumulativeSum2D<int> sum_2d(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum_2d.add(i, j, data[i][j]);
        }
    }
    sum_2d.build();

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum += data[i][j] * mp[i][j];
        }
    }
    sum = abs(sum);
    debug(sum);
    if (sum == 0) {
        cout << "YES" << endl;
        return;
    }

    int g = 0;
    for (int i = 0; i <= n - k; i++) {
        for (int j = 0; j <= m - k; j++) {
            int sx = i, sy = j, gx = i + k, gy = j + k;

            int tmp = sum_2d.query(sx, sy, gx, gy);
            g = gcd(g, abs(tmp));
        }
    }

    if (g == 0 || abs(sum) % g) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
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