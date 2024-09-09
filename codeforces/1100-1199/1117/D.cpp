#include <bits/stdc++.h>

#include "./math/matrix/matrix.hpp"
#include "./math/mint.hpp"

using namespace std;

constexpr int md = 1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

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

void solve() {
    long long n, m;
    cin >> n >> m;
    if (n <= m - 1) {
        cout << 1 << endl;
        return;
    }
    if (n == m) {
        cout << 2 << endl;
        return;
    }

    Matrix<Mint> mat(m, m);
    mat[0][0] = 1;
    mat[0][m - 1] = 1;

    for (int i = 1; i < m; i++) {
        mat[i][i - 1] = 1;
    }

    long long times = n - m;
    auto mat2 = mat ^ times;
    Mint res = 0;
    for (int i = 0; i < m; i++) {
        res += mat2[0][i];
    }
    res += mat2[0][0];
    cout << res << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}