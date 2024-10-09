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
    vector<int> a(n);
    int g = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        g = gcd(g, a[i]);
    }
    for (int i = 0; i < n; i++) {
        a[i] /= g;
    }

    vector<int> vis(n);

    int nowg = 0;
    long long ans = 0;
    int times = 0;
    while (true) {
        int mi_idx = -1;
        for (int i = 0; i < n; i++) {
            if (vis[i] == 0) {
                if (mi_idx == -1 || (gcd(nowg, a[mi_idx]) > gcd(nowg, a[i]))) {
                    mi_idx = i;
                }
            }
        }
        // debug(mi_idx);
        nowg = gcd(nowg, a[mi_idx]);
        if (nowg == 1) {
            ans += n - times;
            break;
        }
        times++;
        ans += nowg;
        vis[mi_idx] = 1;
    }
    cout << ans * g << endl;
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