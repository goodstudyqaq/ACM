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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    int LIMIT = 20;
    long long linf = inf<long long>;
    auto dp = vect(0LL, n, LIMIT);

    function<void(int, int)> dfs = [&](int u, int pre) {
        // debug(u, pre);
        for (int i = 1; i < LIMIT; i++) {
            dp[u][i] = 1LL * i * a[u];
        }
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
            for (int i = 1; i < LIMIT; i++) {
                long long tmp = linf;
                for (int j = 1; j < LIMIT; j++) {
                    if (i == j) continue;
                    tmp = min(tmp, dp[v][j]);
                }
                dp[u][i] += tmp;
            }
        }
    };
    dfs(0, -1);

    long long ans = linf;
    for (int i = 1; i < LIMIT; i++) {
        ans = min(ans, dp[0][i]);
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