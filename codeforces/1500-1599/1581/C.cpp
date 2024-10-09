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
auto vect(const T &v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T &v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

template <class T>
struct CumulativeSum2D {
    vector<vector<T> > data;

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
    int n, m;
    cin >> n >> m;
    vector<string> mp(n);
    for (int i = 0; i < n; i++) {
        cin >> mp[i];
    }

    auto sums = CumulativeSum2D<int>(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sums.add(i, j, mp[i][j] == '0');
        }
    }
    sums.build();

    int a = 5, b = 4;

    vector<int> ct(m);
    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        for (int j = i + a - 1; j < n; j++) {
            for (int k = m - 1; k >= 0; k--) {
                ct[k] = sums.query(i + 1, k, j - 1, k);
                if (k - 1 >= 0) {
                    ct[k] += sums.query(i, 0, i, k - 1);
                    ct[k] += sums.query(j, 0, j, k - 1);
                }
                debug(k, ct[k]);
                if (k + 1 < m) {
                    ct[k] = min(ct[k], ct[k + 1]);
                }
            }

            for (int k = 0; k + b - 1 < m; k++) {
                int k2 = k + b - 1;
                int val = ct[k2];
                val -= (sums.query(i, 0, i, k) + sums.query(j, 0, j, k));
                val += sums.query(i + 1, k, j - 1, k);
                debug(i, j, k, ct);
                ans = min(ans, val);
            }
        }
    }
    cout << ans << endl;
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