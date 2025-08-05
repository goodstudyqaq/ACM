#include <bits/stdc++.h>

#include <set>

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
    long long n, k;
    cin >> n >> k;
    vector<long long> a(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    debug(sum);
    sort(a.begin(), a.end());
    debug(a);
    long long l = a[0], r = a[n - 1];
    // 二分调整之后的最小值
    long long mi = -1;
    // 最后满足：mx - mi <= k + 1

    auto check = [&](long long mi_val) {
        long long need = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] < mi_val) {
                need += (mi_val - a[i]);
            }
        }

        long long have = 0;
        for (int i = 0; i < n; i++) {
            // 大于这个才有必要用 mi_val + k + 1
            if (a[i] > mi_val + k + 1) {
                have += (a[i] - (mi_val + k + 1));
            }
        }
        // debug(have, need);

        if (have >= need) {
            // 才能把所有的都变成不小于 mi_val
            return true;
        }
        return false;
    };

    while (l <= r) {
        long long m = l + r >> 1;
        if (check(m)) {
            mi = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    debug(mi);

    long long need = 0, have = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < mi) {
            need += (mi - a[i]);
            ans += k * (mi - a[i]);
            a[i] = mi;
        }
        if (a[i] > mi + k + 1) {
            have += (a[i] - (mi + k + 1));
            a[i] = mi + k + 1;
        }
    }
    have -= need;
    for (int i = 0; i < n && have; i++) {
        if (a[i] == mi) {
            a[i]++;
            have--;
            ans += k;
        }
    }

    for (int i = 0; i < n && have; i++) {
        if (a[i] == mi + k + 1) {
            a[i]++;
            have--;
        }
    }
    debug(ans);
    debug(a);

    for (int i = 0; i < n; i++) {
        ans += a[i] * (a[i] + 1) / 2;
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