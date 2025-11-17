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
    vector<long long> a(n + 1), sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.begin() + n + 1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }

    auto get_res = [&](int idx) -> long long {
        int len = idx - 1;
        long long res = sum[n];

        int jl = 1;
        int jr = len / k;
        if (len % k) jr++;
        jr = min(jr, n - idx);
        // [jl, jr]
        if (jl > jr) return 0;
        jr--;
        int ansj = 0;
        // debug(idx, jl, jr, len);
        while (jl <= jr) {
            int j = jl + jr >> 1;
            int len2 = j * k;
            len2 = min(len2, idx - 1);
            // debug(jl, jr, j, len2, idx);
            long long tmp = sum[n] + a[idx] * len2 - sum[len2] - (sum[idx + j] - sum[idx] - a[idx] * j);
            int j2 = j + 1;
            len2 = j2 * k;
            len2 = min(len2, idx - 1);
            // debug(j2, len2, idx);
            long long tmp2 = sum[n] + a[idx] * len2 - sum[len2] - (sum[idx + j2] - sum[idx] - a[idx] * j2);
            // debug(tmp, tmp2);
            if (tmp < tmp2) {
                ansj = j;
                jl = j + 1;
            } else {
                jr = j - 1;
            }
        }
        // debug(ansj);
        int j = ansj + 1;
        int len2 = j * k;
        len2 = min(len2, idx - 1);
        long long tmp = sum[n] + a[idx] * len2 - sum[len2] - (sum[idx + j] - sum[idx] - a[idx] * j);
        // debug(idx, j, tmp);
        return tmp;
    };

    long long ans = sum[n];
    for (int i = 1; i <= n; i++) {
        long long tmp = get_res(i);
        ans = max(ans, tmp);
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