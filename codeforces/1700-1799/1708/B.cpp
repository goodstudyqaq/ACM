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
    int n, l, r;
    cin >> n >> l >> r;

    vector<int> ans(n + 1);

    for (int i = 1; i <= n; i++) {
        int tmp = l % i;
        if (tmp == 0) {
            ans[i] = l;
        } else {
            int tmp2 = i - tmp;
            if (l + tmp2 > r) {
                cout << "NO" << endl;
                return;
            }
            ans[i] = l + tmp2;
        }
    }
    cout << "YES" << endl;

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
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
}