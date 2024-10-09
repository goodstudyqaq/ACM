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
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    vector<long long> sum(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum[i] = a[i];
        if (i) sum[i] += sum[i - 1];
    }

    auto get_sum = [&](int block, int idx) -> long long {
        int num = n - block - 1;
        if (idx <= num) {
            return sum[block + idx] - (block == 0 ? 0 : sum[block - 1]);
        } else {
            long long res = sum[n - 1] - sum[block - 1];
            res += sum[idx - num - 1];
            return res;
        }
    };

    while (q--) {
        long long l, r;
        cin >> l >> r;
        l--, r--;
        long long res = 0;

        int l_block = l / n;
        int r_block = r / n;
        // debug(l_block, r_block);

        // 开头为 a[l_block]
        if (l_block != r_block) {
            int l_idx = l % n;
            // debug(l_idx);
            long long tmp = l_idx == 0? 0 : get_sum(l_block, l_idx - 1);
            // debug(tmp);
            res += sum[n - 1] - tmp;
            int r_idx = r % n;
            tmp = get_sum(r_block, r_idx);
            res += tmp;

            int block_num = r_block - l_block - 1;
            res += 1LL * block_num * sum[n - 1];
            cout << res << endl;
        } else {
            int l_idx = l % n, r_idx = r % n;
            res = get_sum(l_block, r_idx);
            if (l_idx) {
                res -= get_sum(l_block, l_idx - 1);
            }
            cout << res << endl;
        }
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