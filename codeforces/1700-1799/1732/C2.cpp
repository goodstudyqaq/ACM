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
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    vector<ll> sum(n + 1);
    vector<ll> xor_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
        xor_sum[i] = xor_sum[i - 1] ^ a[i];
    }

    vector<pii> query(q);
    for (int i = 0; i < q; i++) {
        cin >> query[i].first >> query[i].second;
    }
    const int M = 30;

    vector<vector<int>> V(M);
    vector<vector<int>> sum2(M, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < M; j++) {
            if ((a[i] >> j) & 1) {
                sum2[j][i]++;
                V[j].push_back(i);
            }
            sum2[j][i] += sum2[j][i - 1];
        }
    }

    for (int i = 0; i < q; i++) {
        int L = query[i].first, R = query[i].second;
        ll mx = (sum[R] - sum[L - 1]) - (xor_sum[R] ^ xor_sum[L - 1]);

        if (mx == 0) {
            cout << L << ' ' << L << endl;
            continue;
        }

        auto get = [&](int idx) {
            int l = idx, r = R;
            int res = -1;
            while (l <= r) {
                int m = l + r >> 1;
                ll tmp2 = (sum[m] - sum[idx - 1]) - (xor_sum[m] ^ xor_sum[idx - 1]);
                if (tmp2 == mx) {
                    res = m;
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            return res;
        };

        int ansL = L, ansR = R;
        for (int j = 0; j < M; j++) {
            int tmp = sum2[j][R] - sum2[j][L - 1];
            if (tmp < 2) continue;
            if (tmp % 2 == 0) {
                // 全部都要
                int idx1 = lower_bound(V[j].begin(), V[j].end(), L) - V[j].begin();
                int R = get(V[j][idx1]);
                if (R != -1) {
                    if (ansR - ansL + 1 > R - V[j][idx1] + 1) {
                        ansL = V[j][idx1];
                        ansR = R;
                    }
                }
            } else {
                // 可以丢弃一个
                int idx1 = lower_bound(V[j].begin(), V[j].end(), L) - V[j].begin();
                int R = get(V[j][idx1]);
                if (R != -1) {
                    if (ansR - ansL + 1 > R - V[j][idx1] + 1) {
                        ansL = V[j][idx1];
                        ansR = R;
                    }
                }
                R = get(V[j][idx1 + 1]);
                if (R != -1) {
                    if (ansR - ansL + 1 > R - V[j][idx1 + 1] + 1) {
                        ansL = V[j][idx1 + 1];
                        ansR = R;
                    }
                }
            }
        }
        cout << ansL << ' ' << ansR << endl;
        ll the_ans = (sum[ansR] - sum[ansL - 1]) - (xor_sum[ansR] ^ xor_sum[ansL - 1]);
        debug(the_ans, mx);
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
}