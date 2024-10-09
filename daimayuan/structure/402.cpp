#include <bits/stdc++.h>

#include "./structure/others/sparse-table.hpp"

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
    auto f = [&](ui x, ui y) {
        return max(x, y);
    };

    int n, q;
    cin >> n >> q >> A >> B >> C;
    vector<ui> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rng61();
    }
    debug(a);

    auto st = get_sparse_table(a, f);
    ui ans = 0;

    for (int i = 0; i < q; i++) {
        ui l = rng61() % n, r = rng61() % n;
        if (l > r) swap(l, r);
        ui res = st.fold(l, r + 1);
        ans ^= res;
    }
    cout << ans << endl;
}