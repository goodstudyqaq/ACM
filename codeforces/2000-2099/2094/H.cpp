#include <bits/stdc++.h>

#include <algorithm>

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
    int n, q;
    cin >> n >> q;
    const int B = 200;
    const int M = 1e5;

    vector<int> a(n);
    vector<vector<int>> nxt(n, vector<int>(B + 1, n));
    map<int, vector<int>> m;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > B) {
            for (int j = a[i]; j <= M; j += a[i]) {
                m[j].push_back(i);
            }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 1; j <= B; j++) {
            if (i != n - 1) {
                nxt[i][j] = nxt[i + 1][j];
            }
            if (a[i] <= B) {
                nxt[i][a[i]] = i;
            }
        }
    }

    while (q--) {
        int k, l, r;
        cin >> k >> l >> r;
        l--, r--;
        int now = l;
        int now_val = k;
        long long ans = 0;
        while (now <= r) {
            int go = r + 1;
            for (int i = 1; i <= sqrt(now_val); i++) {
                if (i > B) break;
                if (now_val % i == 0) {
                    if (i != 1) {
                        int idx = nxt[now][i];
                        go = min(go, idx);
                    }
                    int i2 = now_val / i;
                    if (i2 <= B) {
                        int idx = nxt[now][i2];
                        go = min(go, idx);
                    }
                }
            }
            if (now_val > B && m.count(now_val)) {
                int idx = lower_bound(m[now_val].begin(), m[now_val].end(), l) - m[now_val].begin();
                if (idx != m[now_val].size() && m[now_val][idx] <= r) {
                    go = min(go, m[now_val][idx]);
                }
            }

            int times = go - now;
            ans += 1LL * now_val * times;
            if (go <= r) {
                int _a = a[go];
                while (now_val % _a == 0) {
                    now_val /= _a;
                }
            }
            debug(go, now_val);
            now = go;
        }
        cout << ans << '\n';
    }
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