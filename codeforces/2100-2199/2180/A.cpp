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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int l, a, b;
    cin >> l >> a >> b;
    vector<int> vis(l);
    while (vis[a] == 0) {
        vis[a] = 1;
        a = (a + b) % l;
    }
    int mx = 0;
    for (int i = 0; i < l; i++) {
        if (vis[i]) {
            mx = i;
        }
    }
    cout << mx << '\n';
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