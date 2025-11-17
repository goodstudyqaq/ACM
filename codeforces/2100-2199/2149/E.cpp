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
    int n, k, l, r;
    cin >> n >> k >> l >> r;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int L = 0, R = 0;

    map<int, int> M1, M2;

    while (M1.size() < k && L < n) {
        M1[a[L]]++;
        L++;
    }

    if (M1.size() < k) {
        cout << 0 << '\n';
        return;
    }

    while (M2.size() <= k && R < n) {
        M2[a[R]]++;
        R++;
    }

    auto get_interval = [&](int l, int r, int L, int R) {
        int interval_l = max(l, L);
        int interval_r = min(r, R);
        if (interval_l > interval_r) return 0LL;
        return 1LL * interval_r - interval_l + 1;
    };
    debug(L, R);
    long long ans = 0;
    if (M2.size() <= k) {
        ans = get_interval(l, r, L, R);
    } else {
        ans = get_interval(l, r, L, R - 1);
    }

    for (int i = 1; i < n; i++) {
        M1[a[i - 1]]--;
        M2[a[i - 1]]--;
        if (M1[a[i - 1]] == 0) {
            M1.erase(a[i - 1]);
            while (M1.size() < k && L < n) {
                M1[a[L]]++;
                L++;
            }
            if (M1.size() < k) {
                break;
            }
        }

        if (M2[a[i - 1]] == 0) {
            M2.erase(a[i - 1]);
            while (M2.size() <= k && R < n) {
                M2[a[R]]++;
                R++;
            }
        }

        if (M1.size() < k) break;

        if (M2.size() <= k) {
            ans += get_interval(l, r, L - i, R - i);
        } else {
            ans += get_interval(l, r, L - i, R - 1 - i);
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