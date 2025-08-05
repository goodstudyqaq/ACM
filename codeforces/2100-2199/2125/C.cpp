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
    long long l, r;
    cin >> l >> r;

    auto work = [&](long long r) -> long long {
        vector<int> prim{2, 3, 5, 7};

        int sz = prim.size();

        const int LIMIT = 1 << sz;
        long long ans = 0;
        for (int i = 0; i < LIMIT; i++) {
            int val = 1;
            int cnt = 0;
            for (int j = 0; j < sz; j++) {
                if ((i >> j) & 1) {
                    val *= prim[j];
                    cnt++;
                }
            }
            long long num = r / val;

            if (cnt % 2 == 0) {
                ans += num;
            } else {
                ans -= num;
            }
        }
        return ans;
    };

    cout << work(r) - work(l - 1) << '\n';
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