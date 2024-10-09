#include <bits/stdc++.h>

#include "./graph/tree/rmq-lowest-common-ancestor.hpp"

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
unsigned int A, B, C;
inline unsigned int rng61() {
    A ^= A << 16;
    A ^= A >> 5;
    A ^= A << 1;
    unsigned int t = A;
    A = B;
    B = C;
    C ^= t ^ A;
    return C;
}
typedef unsigned int ui;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m >> A >> B >> C;
    // 输入树边
    RMQLowestCommonAncestor<> g(n);
    g.read(n - 1, -1, false, false);
    g.build(0);
    long long ans = 0;
    for (int i = 1; i <= m; i++) {
        unsigned int u = rng61() % n + 1, v = rng61() % n + 1;
        u--, v--;
        ans ^= (1LL * i * (g.lca(u, v) + 1));
    }
    cout << ans << endl;
}