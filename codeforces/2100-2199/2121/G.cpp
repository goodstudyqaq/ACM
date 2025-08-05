#include <bits/stdc++.h>

#include "./structure/others/binary-indexed-tree.hpp"

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
    int n;
    string s;
    cin >> n >> s;
    int mx = 2 * n + 1;
    BIT<long long> bit1(mx), bit2(mx), bit3(mx);

    vector<int> sum(n + 1);
    sum[0] = n + 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            sum[i + 1] = 1;
        } else {
            sum[i + 1] = -1;
        }
        sum[i + 1] += sum[i];
    }

    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        int val = sum[i];
        // 小于等于 val 的都表示 1 多
        // 2num1 = sumi + i - (sumj + j)
        long long tmp1 = bit1.query(val);
        int num = bit3.query(val);
        ans += 1LL * (val + i) * num - tmp1;
        // debug(i, ans);

        long long tmp2 = bit2.query(mx) - bit2.query(val);
        int num2 = bit3.query(mx) - num;
        ans += 1LL * (i - val) * num2 - tmp2;
        // debug(i, ans, "zz");

        // 大于 val 的表示 0 多
        bit1.add(val, i + val);
        bit2.add(val, i - val);
        bit3.add(val, 1);
    }
    cout << ans / 2 << '\n';
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