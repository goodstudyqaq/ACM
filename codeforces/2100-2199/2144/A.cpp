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

    vector<int> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= 3;
        sum[i] = (sum[i - 1] + a[i]) % 3;
    }

    for (int l = 1; l < n; l++) {
        for (int r = l + 1; r < n; r++) {
            int s1 = sum[l];
            int s2 = (sum[r] - sum[l] + 3) % 3;
            int s3 = (sum[n] - sum[r] + 3) % 3;
            if (s1 == s2 && s1 == s3) {
                cout << l << ' ' << r << '\n';
                return;
            }
            if (s1 != s2 && s1 != s3 && s2 != s3) {
                cout << l << ' ' << r << '\n';
                return;
            }
        }
    }
    cout << 0 << ' ' << 0 << '\n';
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