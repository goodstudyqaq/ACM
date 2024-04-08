#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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

    vector<long long> len2(n);
    vector<long long> real_len(n);
    vector<long long> times(n);
    const long long limit = (long long)(1e18) + 5;
    debug(limit);

    vector<pair<int, int>> op(n);
    for (int i = 0; i < n; i++) {
        int b, x;
        cin >> b >> x;
        op[i] = {b, x};
        if (b == 1) {
            times[i] = 1;
            if (i == 0) {
                len2[i] = 1;
                real_len[i] = 1;
            } else {
                if (op[i - 1].first == 1) {
                    len2[i] = min(len2[i - 1] + 1, limit);
                    real_len[i] = min(real_len[i - 1] + 1, limit);
                } else {
                    len2[i] = min(real_len[i - 1] + 1, limit);
                    real_len[i] = min(real_len[i - 1] + 1, limit);
                }
            }
        } else {
            if (times[i - 1] > limit / (x + 1)) {
                times[i] = limit;
            } else {
                times[i] = times[i - 1] * (x + 1);
            }
            len2[i] = len2[i - 1];

            if (real_len[i - 1] > limit / (x + 1)) {
                real_len[i] = limit;
            } else {
                real_len[i] = real_len[i - 1] * (x + 1);
            }
        }
    }
    debug(len2);
    debug(real_len);
    debug(times);

    function<int(long long)> work = [&](long long u) -> int {
        int idx = lower_bound(real_len.begin(), real_len.end(), u) - real_len.begin();
        // debug(u, idx);

        if (op[idx].first == 1) {
            return op[idx].second;
        }
        long long the_len2 = len2[idx];
        long long the_times = times[idx];
        // the_len2 循环了 the_times 次
        return work((u - 1) % the_len2 + 1);
    };

    for (int i = 0; i < q; i++) {
        long long k;
        cin >> k;
        // k--;
        // debug(k);
        cout << work(k) << ' ';
    }
    cout << endl;
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