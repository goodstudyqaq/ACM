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
    int n;
    cin >> n;

    vector<int> a(n);
    map<int, int> M;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        M[a[i]]++;
    }

    vector<int> V;
    for (auto it : M) {
        V.push_back(it.second);
    }

    auto work = [&](vector<int> &v) -> int {
        int sz = V.size();
        vector<int> pre_sum(sz), suf_sum(sz);
        for (int i = 0; i < sz; i++) {
            pre_sum[i] = V[i];
            if (i > 0) {
                pre_sum[i] += pre_sum[i - 1];
            }
        }

        for (int i = sz - 1; i >= 0; i--) {
            suf_sum[i] = V[i];
            if (i != sz - 1) {
                suf_sum[i] += suf_sum[i + 1];
            }
        }

        int res = numeric_limits<int>::max() / 2;

        auto work2 = [&](int b) {
            int l = 0, r = sz - 1;
            int ans = -1;
            while (l <= r) {
                int m = l + r >> 1;
                if (pre_sum[m] <= (1 << b)) {
                    ans = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
            return ans;
        };

        auto work3 = [&](int b, int l) {
            int r = sz - 1;
            int ans = -1;
            while (l <= r) {
                int m = l + r >> 1;
                if (suf_sum[m] <= (1 << b)) {
                    ans = m;
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            return ans;
        };

        for (int i = 0; i < 19; i++) {
            int idx = work2(i);
            if (idx == -1) continue;
            if (idx == sz - 1) {
                res = min(res, 2 + (1 << i) - n);
                break;
            }
            int cnt1 = (1 << i) - pre_sum[idx];
            for (int i2 = 0; i2 < 19; i2++) {
                int idx2 = work3(i2, idx + 1);
                if (idx2 == -1) continue;
                int cnt2 = (1 << i2) - suf_sum[idx2];
                int have = n - pre_sum[idx] - suf_sum[idx2];
                int now = 1;
                while (now < have) now *= 2;
                int cnt3 = now - have;
                res = min(res, cnt1 + cnt2 + cnt3);
            }
        }
        return res;
    };

    int res = work(V);
    reverse(V.begin(), V.end());
    int res2 = work(V);
    cout << min(res, res2) << endl;
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
}