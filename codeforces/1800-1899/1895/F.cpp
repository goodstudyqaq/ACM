#include <bits/stdc++.h>

#include "./math/matrix/matrix.hpp"
#include "./math/mint.hpp"

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
constexpr int md = 1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

void solve() {
    int n, x, k;
    cin >> n >> x >> k;
    Mint res = Mint(x + k) * power(Mint(2 * k + 1), n - 1);

    Matrix<Mint> mat(x);

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            if (abs(i - j) <= k) {
                mat[i][j] = 1;
            }
        }
    }

    mat = mat ^ (n - 1);
    Mint res2 = 0;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            res2 += mat[i][j];
        }
    }
    debug(res, res2);
    cout << res - res2 << endl;
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