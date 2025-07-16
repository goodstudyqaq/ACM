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
    int n;
    cin >> n;

    typedef array<int, 3> a3;
    vector<a3> op;
    for (int i = 2; i <= n; i++) {
        op.push_back({i, 1, i});
    }
    for (int i = 1; i < n; i++) {
        op.push_back({i, i + 1, n});
    }
    cout << op.size() << '\n';
    for (auto it : op) {
        cout << it[0] << ' ' << it[1] << ' ' << it[2] << '\n';
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