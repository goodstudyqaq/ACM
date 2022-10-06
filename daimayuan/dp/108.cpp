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
// template <class T>
// auto vect(const T& v, int n) { return vector<T>(n, v); }
// template <class T, class... D>
// auto vect(const T& v, int n, D... m) {
//     return vector<decltype(vect(v, m...))>(n, vect(v, m...));
// }

// template <typename T>
// static constexpr T inf = numeric_limits<T>::max() / 2;
// mt19937_64 mrand(random_device{}());
// long long rnd(long long x) { return mrand() % x; }
// int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> V(n + 1);
    vector<int> hp(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        V[p].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        cin >> hp[i];
    }
    const ll inf = 1e18;
    vector<vector<vector<ll>>> dp;
    dp.resize(n + 1, vector<vector<ll>>(n + 1, vector<ll>(2, inf)));

    // dp[i][j][0/1] i 的子树用了 j 次魔法，i自身有没有用的最小代价
    vector<int> sz(n + 1);
    vector<ll> tmp(n + 1);
    vector<ll> tmp2(n + 1);

    function<void(int)> dfs = [&](int u) {
        dp[u][0][0] = hp[u];
        dp[u][1][1] = 0;
        sz[u] = 1;
        for (auto v : V[u]) {
            dfs(v);
            int v_sz = sz[v];
            int u_sz = sz[u];
            // 先计算没用
            for (int i = 0; i <= u_sz + v_sz; i++) {
                tmp[i] = inf;
                tmp2[i] = inf;
            }

            for (int i = 0; i <= u_sz; i++) {
                for (int j = 0; j <= v_sz; j++) {
                    tmp[i + j] = min({tmp[i + j], dp[u][i][0] + dp[v][j][0] + hp[v], dp[u][i][0] + dp[v][j][1]});
                    tmp2[i + j] = min({tmp2[i + j], dp[u][i][1] + dp[v][j][0], dp[u][i][1] + dp[v][j][1]});
                }
            }

            for (int i = 0; i <= u_sz + v_sz; i++) {
                dp[u][i][0] = tmp[i];
                dp[u][i][1] = tmp2[i];
            }
            sz[u] += sz[v];
        }
    };

    dfs(1);
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 0; j <= sz[i]; j++) {
    //         debug(i, j, dp[i][j][0], dp[i][j][1]);
    //     }
    // }

    for (int i = 0; i <= n; i++) {
        cout << min(dp[1][i][0], dp[1][i][1]) << ' ';
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