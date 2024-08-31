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
    int n, m;
    cin >> n >> m;
    vector<vector<string>> mp(2, vector<string>(n));
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < n; i++) {
            cin >> mp[j][i];
        }
    }
    auto V = vect(0, 2, n, m);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                V[i][j][k] = mp[i][j][k] - '0';
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (V[0][i][j] != V[1][i][j]) {
                if (i == n - 1 || j == m - 1) {
                    cout << "NO" << endl;
                    return;
                }
                int tmp = (V[1][i][j] - V[0][i][j] + 3) % 3;
                (V[0][i][j] += tmp) %= 3;
                (V[0][i + 1][j + 1] += tmp) %= 3;
                tmp = 3 - tmp;
                (V[0][i][j + 1] += tmp) %= 3;
                (V[0][i + 1][j] += tmp) %= 3;
            }
        }
    }
    cout << "YES" << endl;
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