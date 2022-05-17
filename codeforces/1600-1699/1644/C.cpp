#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n + 1), sum(n + 1);
    int inf = numeric_limits<int>::max() / 2;
    vector<int> ans(n + 1, -inf);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int len = j - i + 1;
            ans[len] = max(ans[len], sum[j] - sum[i - 1]);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = max(ans[i], ans[i + 1]);
    }
    debug(ans);
    int mx = 0;
    for (int i = 0; i <= n; i++) {
        int val = ans[i] + x * i;
        mx = max(mx, val);
        cout << mx << ' ';
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