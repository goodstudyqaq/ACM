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

void solve() {
    long long n, l, r, k;
    cin >> n >> l >> r >> k;

    if (n % 2) {
        cout << l << '\n';
        return;
    }

    auto get_v = [&](long long val) {
        vector<int> v;
        while (val) {
            v.push_back(val % 2);
            val /= 2;
        }
        return v;
    };

    auto v1 = get_v(l);
    auto v2 = get_v(r);
    if (v1.size() == v2.size()) {
        cout << -1 << '\n';
        return;
    }

    if (n == 2) {
        cout << -1 << '\n';
        return;
    }

    // 前 n - 2 输出 l, 后面输出 1 << v2.size()

    if (k <= n - 2) {
        cout << l << '\n';
    } else {
        cout << (1LL << (v1.size())) << '\n';
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