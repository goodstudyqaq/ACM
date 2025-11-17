#include <bits/stdc++.h>

#include <limits>
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
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    const int LIMIT = 31;
    int or_sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        or_sum |= a[i];
    }
    // debug(bit);

    vector<int> a2(n);
    auto get_cost = [&](int idx) {
        const long long cut = (1LL << (idx + 1)) - 1;
        for (int i = 0; i < n; i++) {
            a2[i] = a[i] & cut;
        }
        int ans = 0;
        for (int i = idx; i >= 0; i--) {
            int choose = 0;
            int limit = 1 << i;
            for (int j = 0; j < n; j++) {
                if (a2[j] >= limit) {
                    choose = -1;
                    a2[j] -= limit;
                }
                if (choose != -1 && a2[choose] < a2[j]) {
                    choose = j;
                }
            }
            if (choose != -1) {
                int val = limit - a2[choose];
                ans += val;
                a2[choose] = 0;
            }
        }
        return ans;
    };

    vector<int> cost(LIMIT);
    for (int i = 0; i < LIMIT; i++) {
        int ct = get_cost(i);
        cost[i] = ct;
    }

    while (q--) {
        int b;
        cin >> b;
        int ans = __builtin_popcount(or_sum);
        for (int i = 0; i < LIMIT; i++) {
            if (cost[i] <= b) {
                int res = __builtin_popcount(or_sum >> (i + 1)) + (i + 1);
                ans = max(ans, res);
            }
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