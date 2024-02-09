#include <bits/stdc++.h>

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
    long long a, b, r;
    cin >> a >> b >> r;

    auto work = [&](long long r) {
        const int BIT_LIMIT = 60;
        vector<int> bit_a(BIT_LIMIT), bit_b(BIT_LIMIT), bit_r(BIT_LIMIT);
        for (int i = 0; i < BIT_LIMIT; i++) {
            bit_a[i] = (a >> i) & 1;
            bit_b[i] = (b >> i) & 1;
            bit_r[i] = (r >> i) & 1;
        }
        function<void(int, bool, long long &)> dfs = [&](int d, bool limit, long long &val) -> void {
            if (d == -1) return;
            if (limit) {
                if (bit_r[d] == 0) {
                    long long tmp = (bit_a[d] - bit_b[d]) * (1LL << d);
                    val += tmp;
                    dfs(d - 1, limit, val);
                } else {
                    if (bit_a[d] == bit_b[d]) {
                        dfs(d - 1, false, val);
                    } else {
                        if (((val > 0) && (bit_a[d] == 1)) || ((val < 0) && (bit_a[d] == 0))) {
                            long long tmp = abs(bit_a[d] - bit_b[d]) * (1LL << d);
                            if (val > 0)
                                val -= tmp;
                            else
                                val += tmp;
                            dfs(d - 1, true, val);
                        } else {
                            long long tmp = (bit_a[d] - bit_b[d]) * (1LL << d);
                            val += tmp;
                            dfs(d - 1, false, val);
                        }
                    }
                }

            } else {
                long long tmp = abs(bit_a[d] - bit_b[d]) * (1LL << d);
                if (val > 0)
                    val -= tmp;
                else
                    val += tmp;
                dfs(d - 1, false, val);
            }
        };
        long long ans = 0;
        dfs(BIT_LIMIT - 1, true, ans);
        return ans;
    };

    cout << abs(work(r)) << endl;
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