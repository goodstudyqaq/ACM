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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> cnt(m + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = i + i; j <= m; j += i) {
            cnt[i] += cnt[j];
        }
    }
    // debug(cnt);

    auto get_prm = [&](int val) {
        vector<int> prm;
        for (int i = 2; i <= sqrt(val); i++) {
            if (val % i == 0) {
                prm.push_back(i);
                while (val % i == 0) {
                    val /= i;
                }
            }
        }
        if (val != 1) {
            prm.push_back(val);
        }
        return prm;
    };

    vector<int> dp(n);
    for (int i = 0; i < n; i++) {
        int val = a[i];

        if (val == 1) {
            dp[i] = n - 1;
            continue;
        }

        vector<int> prm = get_prm(val);

        int sz = prm.size();
        const int LIMIT = 1 << sz;
        for (int j = 0; j < LIMIT; j++) {
            int num = 1;
            int one_num = 0;
            for (int k = 0; k < sz; k++) {
                if ((j >> k) & 1) {
                    num *= prm[k];
                    one_num++;
                }
            }
            if (one_num % 2 == 0) {
                dp[i] += cnt[num];
            } else {
                dp[i] -= cnt[num];
            }
        }
    }

    // 找 dp[i] 最大的 i
    int u1 = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > dp[u1]) {
            u1 = i;
        }
    }
    if (dp[u1] == 0) {
        cout << 0 << '\n';
        return;
    }

    int v1 = -1;
    for (int i = 0; i < n; i++) {
        if (i == u1) continue;
        if (gcd(a[u1], a[i]) == 1) {
            if (v1 == -1 || dp[i] < dp[v1]) {
                v1 = i;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (i == u1) continue;
        if (gcd(a[i], a[u1]) == 1) {
            dp[i]--;
        }
    }
    for (int i = 0; i < n; i++) {
        if (i == v1) continue;
        if (gcd(a[i], a[v1]) == 1) {
            dp[i]--;
        }
    }

    int u2 = -1;
    for (int i = 0; i < n; i++) {
        if (i == u1 || i == v1) continue;
        if (dp[i] > 0) {
            u2 = i;
            break;
        }
    }
    if (u2 == -1) {
        cout << 0 << '\n';
        return;
    }
    int v2 = -1;
    for (int i = 0; i < n; i++) {
        if (i == u1 || i == v1 || i == u2) continue;
        if (gcd(a[i], a[u2]) == 1) {
            v2 = i;
            break;
        }
    }
    
    cout << u1 + 1 << ' ' << v1 + 1 << ' ' << u2 + 1 << ' ' << v2 + 1 << '\n';
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