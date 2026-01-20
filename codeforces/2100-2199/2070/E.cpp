#include <bits/stdc++.h>

#include "structure/others/binary-indexed-tree.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef array<int, 2> a2;

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

    if (n == 1) {
        cout << 0 << '\n';
        return;
    }

    int start = -1;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] != s[i + 1]) {
            start = i + 1;
            break;
        }
    }
    if (start == -1) {
        // 全部都一样
        if (s[0] == '0') {
            ll ans = 1LL * n * (n - 1) / 2;
            cout << ans << '\n';
        } else {
            cout << 0 << '\n';
        }
        return;
    }

    vector<vector<int>> sum(n, vector<int>(2));
    vector<int> sum2(n);

    int mi = 1e9;
    int mx = -1e9;

    for (int i = 0; i < n; i++) {
        sum[i][s[i] - '0']++;
        sum2[i] = sum[i][0] - 3 * sum[i][1];
        if (i) {
            sum[i][0] += sum[i - 1][0];
            sum[i][1] += sum[i - 1][1];
            sum2[i] += sum2[i - 1];
        }
        mi = min(mi, sum2[i]);
        mx = max(mx, sum2[i]);
    }
    mx++;
    mi = min(mi, 0);
    debug(mi, mx);
    BIT<int> bit(mi, mx);
    bit.add(0, 1);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        debug(i);
        int v1 = sum2[i];
        if (v1 - 2 >= mi) {
            int sub_ans = bit.query(v1 - 2);
            ans += sub_ans;
            debug(i, sub_ans);
        }

        int sub_ans2 = bit.query(v1 + 1) - bit.query(v1);
        ans += sub_ans2;

        bit.add(v1, 1);
    }
    cout << ans << '\n';
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}