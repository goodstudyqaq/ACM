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
    int n, k;
    cin >> n >> k;

    vector<int> a(n), b(k);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < k; i++) {
        cin >> b[i];
    }
    sort(b.begin(), b.end());

    long long ans = 0;

    int now = n - 1;
    int b_idx = 0;
    while (now >= 0) {
        if (b_idx >= k) {
            while (now >= 0) {
                ans += a[now];
                now--;
            }
            break;
        } else {
            int _b = b[b_idx];
            for (int i = 0; i < _b - 1 && now - i >= 0; i++) {
                int idx = now - i;
                ans += a[idx];
            }
            now -= _b;
            b_idx++;
        }
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