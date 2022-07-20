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

const int maxn = 1e5 + 5;
int f[maxn];
int find(int u) {
    return u == f[u] ? u : f[u] = find(f[u]);
}

template <typename T>
struct RMQ {
    int n = 0, levels = 0;
    vector<T> values;
    vector<vector<int>> range_high;
    function<bool(T, T)> func;

    // RMQ(const vector<T>& _values = {}) {
    //     func = f;
    //     if (!_values.empty())
    //         build(_values);
    // }

    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }

    int max_index(int a, int b) const {
        return func(values[a], values[b]) ? a : b;
        // return values[a] > values[b] ? a : b;
    }

    void build(const vector<T>& _values, function<bool(T, T)> f) {
        func = f;
        values = _values;
        n = values.size();
        levels = largest_bit(n) + 1;
        range_high.resize(levels);

        for (int k = 0; k < levels; k++)
            range_high[k].resize(n - (1 << k) + 1);

        for (int i = 0; i < n; i++)
            range_high[0][i] = i;

        for (int k = 1; k < levels; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                range_high[k][i] = max_index(range_high[k - 1][i], range_high[k - 1][i + (1 << (k - 1))]);
    }
    // [a, b)
    int rmq_index(int a, int b) const {
        assert(a < b);
        int level = largest_bit(b - a);
        return max_index(range_high[level][a], range_high[level][b - (1 << level)]);
    }

    T rmq_value(int a, int b) const {
        int idx = rmq_index(a, b);

        return values[idx];
    }
};
static int largest_bit(int x) {
    return 31 - __builtin_clz(x);
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) f[i] = i;

    vector<vector<pii>> V(n + 1);

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            V[u].push_back({v, i});
            V[v].push_back({u, i});
            f[fu] = fv;
        }
    }
    debug(V);

    vector<int> dep(n + 1);
    vector<vector<int>> fa, val;
    fa.resize(n + 1, vector<int>(20, 0));
    val.resize(n + 1, vector<int>(20, 0));
    function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
        dep[u] = d;
        for (auto it : V[u]) {
            if (it.first == pre) continue;
            fa[it.first][0] = u;
            val[it.first][0] = it.second;
            dfs(it.first, u, d + 1);
        }
    };
    dfs(1, 0, 0);

    auto rmq = [&]() {
        for (int i = 1; i < 20; i++) {
            for (int j = 1; j <= n; j++) {
                if ((1 << i) > dep[j]) continue;
                int k = fa[j][i - 1];
                fa[j][i] = fa[k][i - 1];
                val[j][i] = max(val[j][i - 1], val[k][i - 1]);
            }
        }
    };
    rmq();
    // debug(val);

    auto query = [&](int x, int y) {
        if (dep[x] > dep[y]) swap(x, y);

        int ans = 0;
        for (int j = 19; j >= 0 && dep[x] != dep[y]; j--) {
            if (dep[y] - (1 << j) < dep[x]) continue;
            ans = max(ans, val[y][j]);
            y = fa[y][j];
        }

        if (x == y) return ans;

        for (int j = 19; j >= 0; j--) {
            if (dep[x] - (1 << j) < 0 || fa[x][j] == fa[y][j]) continue;
            ans = max(ans, val[x][j]);
            ans = max(ans, val[y][j]);
            x = fa[x][j], y = fa[y][j];
        }
        ans = max({ans, val[x][0], val[y][0]});
        return ans;
    };

    vector<int> w(n + 1);
    for (int i = 2; i <= n; i++) {
        int val = query(i - 1, i);
        w[i] = val;
    }
    RMQ<int> rmq2;
    rmq2.build(w, [&](int a, int b) -> bool {
        return a > b;
    });
    debug(w);
    debug(rmq2.levels);

    // int q;
    // cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        if (l == r) {
            cout << 0 << ' ';
            continue;
        }
        int res = rmq2.rmq_value(l + 1, r + 1);
        cout << res << ' ';
    }
    cout << endl;
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