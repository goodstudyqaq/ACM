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
    int n;
    cin >> n;
    vector<int> a(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        ans += abs(a[i] - a[i + 1]);
    }

    int res = ans;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            int tmp = abs(a[0] - a[1]);
            res = min(res, ans - tmp);
        } else if (i == n - 1) {
            int tmp = abs(a[n - 1] - a[n - 2]);
            res = min(res, ans - tmp);
        } else {
            int tmp = abs(a[i] - a[i - 1]) + abs(a[i + 1] - a[i]) - abs(a[i + 1] - a[i - 1]);
            res = min(res, ans - tmp);
        }
    }
    cout << res << '\n';
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