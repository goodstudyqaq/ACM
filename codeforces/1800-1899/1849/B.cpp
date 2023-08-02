#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= k;
        if (a[i] == 0) a[i] = k;
    }
    vector<int> f(n + 1);
    iota(f.begin() + 1, f.begin() + 1 + n, 1);

    sort(f.begin() + 1, f.begin() + 1 + n, [&](int x, int y) {
        if (a[x] != a[y])
            return a[x] > a[y];
        return x < y;
    });

    for (int i = 1; i <= n; i++) {
        cout << f[i] << ' ';
    }
    cout << endl;
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