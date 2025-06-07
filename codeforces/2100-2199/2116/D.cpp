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
    int n, q;
    cin >> n >> q;
    vector<int> b(n + 1);
    vector<int> big(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        big[i] = b[i];
    }

    typedef array<int, 3> a3;
    vector<a3> query(q);
    for (int i = 0; i < q; i++) {
        cin >> query[i][0] >> query[i][1] >> query[i][2];
    }

    for (int i = q - 1; i >= 0; i--) {
        auto [x, y, z] = query[i];

        big[x] = max(big[x], big[z]);
        big[y] = max(big[y], big[z]);
    }
    auto a = big;

    for (int i = 0; i < q; i++) {
        auto [x, y, z] = query[i];
        int val = min(a[x], a[y]);
        a[z] = val;
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) {
            cout << -1 << '\n';
            return;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << big[i] << ' ';
    }
    cout << '\n';
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