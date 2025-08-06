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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> mi(n + 1);
    vector<int> mx(n + 2);
    mi[0] = 1e9;

    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        mi[i] = min(mi[i - 1], a[i]);
    }
    for (int i = n; i >= 1; i--) {
        mx[i] = max(mx[i + 1], a[i]);
    }

    for (int i = 1; i <= n; i++) {
        int val = a[i];
        if (val == mi[i]) {
            ans[i] = 1;
        }
        if (val == mx[i]) {
            ans[i] = 1;
        }
        cout << ans[i];
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