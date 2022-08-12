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
    int n, q;
    cin >> n >> q;
    vector<ll> a(n + 1);
    vector<ll> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.begin() + 1 + n);
    for (int i = 1; i <= n; i++) {
        sum[i] = a[i] + sum[i - 1];
    }
    debug(a, sum);
    while (q--) {
        int x, y;
        cin >> x >> y;
        int L = n - x + 1;
        int R = L + y - 1;
        debug(L, R);
        cout << sum[R] - sum[L - 1] << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    solve();
}