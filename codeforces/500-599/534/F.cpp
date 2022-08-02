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

template <class T>
auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T& v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    vector<int> a, b;
    a.resize(n);
    b.resize(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    int LIMIT = 1 << n;
    vector<int> v(n);
    vector<vector<int>> status(4);
    for (int i = 0; i < LIMIT; i++) {
        for (int j = 0; j < n; j++) {
            v[j] = (i >> j) & 1;
        }
        int black_num = 0;
        int black_idx = -2;
        for (int j = 0; j < n; j++) {
            if (v[j]) {
                if (black_idx != j - 1) {
                    black_num++;
                }
                black_idx = j;
            }
        }
        status[black_num].push_back(i);
    }
    debug(status);
    set<int> ha[20][33];
    vector<vector<char>> ans(n, vector<char>(m));
    auto dfs = [&](auto self, int idx, int pre, int h) {
        if (idx == m) {
            bool f = true;
            for (int i = 0; i < n; i++) {
                if (a[i]) {
                    f = false;
                    break;
                }
            }
            return f;
        }
        if (ha[idx][pre].count(h)) return false;
        for (int i = 0; i < n; i++) {
            int need = a[i];
            int len = m - idx;
            if (need > (len - 1) / 2 + 1) return false;
        }

        int the_b = b[idx];
        for (auto s : status[the_b]) {
            for (int j = 0; j < n; j++) {
                if (((s >> j) & 1) == 1 && ((pre >> j) & 1) == 0) {
                    a[j]--;
                }
            }
            bool f = true;
            int h2 = 0;
            for (int j = 0; j < n; j++) {
                if (a[j] < 0) {
                    f = false;
                    break;
                }
                h2 = h2 * 11 + a[j];
            }

            if (f) {
                bool res = self(self, idx + 1, s, h2);
                if (res) {
                    for (int j = 0; j < n; j++) {
                        if ((s >> j) & 1) {
                            ans[j][idx] = '*';
                        } else {
                            ans[j][idx] = '.';
                        }
                    }
                    return true;
                }
            }
            for (int j = 0; j < n; j++) {
                if ((s >> j) & 1 && ((pre >> j) & 1) == 0) {
                    a[j]++;
                }
            }
        }
        ha[idx][pre].insert(h);
        return false;
    };
    dfs(dfs, 0, 0, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[i][j];
        }
        cout << endl;
    }
    return 0;
}