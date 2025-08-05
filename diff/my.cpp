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
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    int val = n;
    long long ans = 0;
    int now = 0;
    vector<int> vis(n);
    while (now < n) {
        while (now < n && p[now] != val) {
            now++;
        }
        if (now == n) break;
        vis[now] = 1;
        val--;
        now++;
    }

    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            ans += 1LL * (i + 1) * (n - i);
        } else {
            if (i + 1 < n && vis[i + 1] == 0 && p[i] > p[i + 1]) {
                ans += 2LL * (i + 1);
            } else {
                ans += 1LL * (i + 1);
            }
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