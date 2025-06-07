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
    string s;
    cin >> n >> s;
    vector<int> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '1') {
            sum[i] = 1;
        } else {
            sum[i] = 0;
        }
        sum[i] += sum[i - 1];
    }

    if (sum[n] == 0) {
        cout << 0 << '\n';
        return;
    }

    int ans = n;
    set<int> S;
    for (int r = 1; r <= n; r++) {
        S.insert(r - 2 * sum[r - 1]);
        int b = *S.rbegin();
        int tmp = sum[n] + r - 2 * sum[r] - b + 1;
        ans = min(ans, tmp);
    }
    cout << ans << '\n';
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