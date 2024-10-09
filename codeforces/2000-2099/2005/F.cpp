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
    int l, n, m;
    cin >> l >> n >> m;
    vector<int> a(l);
    for (int i = 0; i < l; i++) {
        cin >> a[i];
    }

    map<int, int> M;
    for (int i = 0; i < l; i++) {
        if (M.count(a[i])) {
            l = i;
            a.resize(i);
            break;
        }
        M[a[i]] = i;
    }

    vector<vector<int>> b(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> b[i][j];
        }
    }

    auto dp = vect(1000000000, 2, n + 1, m + 1);

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            dp[0][i][j] = min(dp[0][i + 1][j], dp[0][i][j + 1]);
            dp[1][i][j] = min(dp[1][i + 1][j], dp[1][i][j + 1]);
            if (M.count(b[i][j])) {
                int idx = M[b[i][j]];
                int f = idx % 2;
                if (idx + 1 < dp[f ^ 1][i + 1][j + 1]) {
                    dp[f][i][j] = min(dp[f][i][j], idx);
                }
            }
        }
    }
    if (dp[0][0][0] == 0) {
        cout << 'T' << endl;
    } else {
        cout << 'N' << endl;
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