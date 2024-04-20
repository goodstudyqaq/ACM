#include <bits/stdc++.h>

#include <limits>

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
    int n;
    cin >> n;
    vector<int> h(n + 1);
    vector<long long> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        sum[i] = sum[i - 1] + h[i];
    }

    vector<int> stk;
    vector<long long> ct(n + 1), ct2(n + 1);

    auto work = [&](vector<long long> &ct) {
        stk.clear();
        for (int i = n; i >= 1; i--) {
            while (!stk.empty() && h[stk.back()] + stk.back() >= h[i] + i) {
                stk.pop_back();
            }
            int flag = -1;

            if (stk.size() != 0) {
                flag = stk.back();
            }

            if (flag == -1) {
                int r = h[i] + i;
                // 会在 r 变成 0
                r = min(r, n + 1);
                long long val = sum[n] - sum[r - 1];

                long long val2 = sum[r - 1] - sum[i];
                int number = r - 1 - i;
                long long val3 = 1LL * h[i] * number - 1LL * (1 + number) * number / 2;
                val2 -= val3;
                ct[i] = val + val2;
            } else {
                ct[i] = ct[flag];
                int number = flag - 1 - i;
                long long val2 = sum[flag - 1] - sum[i];
                long long val3 = 1LL * h[i] * number - 1LL * (1 + number) * number / 2;
                val2 -= val3;
                ct[i] += val2;
            }
            stk.push_back(i);
        }
    };

    work(ct);
    debug(ct);
    reverse(h.begin() + 1, h.begin() + 1 + n);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + h[i];
    }
    work(ct2);
    reverse(ct2.begin() + 1, ct2.begin() + 1 + n);
    debug(ct2);

    reverse(h.begin() + 1, h.begin() + 1 + n);

    long long ans = numeric_limits<long long>::max() / 2;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, ct[i] + ct2[i] + h[i]);
    }
    cout << ans << endl;
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