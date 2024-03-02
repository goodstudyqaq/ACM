#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    long long inf = numeric_limits<long long>::max() / 2;

    auto get_max_mi = [&](vector<long long> &tmp, int delete_num) {
        // debug(tmp, delete_num);
        auto mi = *min_element(tmp.begin(), tmp.end());

        long long l = -inf, r = mi;
        long long ans = -1;

        auto check = [&](long long val) {
            long long use = 0;
            for (int i = 0; i < tmp.size(); i++) {
                use += tmp[i] - val;
                if (use >= delete_num) {
                    return true;
                }
            }
            return false;
        };

        while (l <= r) {
            long long m = l + r >> 1;
            if (check(m)) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return ans;
    };

    auto work = [&](int k) -> long long {
        auto tmpa = a;
        if (k <= n) {
            // add 1, 2, 3, ... k
            for (int i = 1; i <= k; i++) {
                tmpa[i - 1] += k - i + 1;
            }
            return get_max_mi(tmpa, 0);
        }

        int begin = k - n;

        if ((k - n) % 2)
            begin += 2;
        else
            begin += 1;

        // add begin, begin + 1, begin + 2, .. k
        for (int i = begin; i <= k; i++) {
            tmpa[i - begin] += k - i + begin;
        }
        return get_max_mi(tmpa, begin / 2);
    };

    while (q--) {
        int k;
        cin >> k;
        cout << work(k) << ' ';
    }
    cout << endl;
    return 0;
}