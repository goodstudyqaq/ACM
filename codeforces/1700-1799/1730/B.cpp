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
    vector<int> x(n), t(n);
    vector<pii> V(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        V[i].first = x[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> t[i];
        V[i].second = t[i];
    }
    sort(V.begin(), V.end());

    vector<int> mx1(n), mx2(n);
    for (int i = 0; i < n; i++) {
        mx1[i] = V[i].second - V[i].first;
        if (i > 0) {
            mx1[i] = max(mx1[i], mx1[i - 1]);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        mx2[i] = V[i].second + V[i].first;
        if (i != n - 1) {
            mx2[i] = max(mx2[i], mx2[i + 1]);
        }
    }

    double res = numeric_limits<double>::max() / 2;
    double res_x;
    for (int i = 0; i < n; i++) {
        // [0, i]
        double tmp1 = mx1[i] + V[i].first;
        double cx = V[i].first;
        if (i != n - 1) {
            double tmp2 = mx2[i + 1] - V[i + 1].first;
            double tmp3 = V[i + 1].first - V[i].first;
            double tmpx = (tmp2 + tmp3 - tmp1) / 2.0;
            // debug(i, V[i], tmpx, tmp1, tmp2, tmp3);
            if (tmpx >= 0 && tmpx <= tmp3) {
                double tmp4 = tmp1 + tmpx;
                tmp1 = tmp4;
                cx = tmpx + V[i].first;
            } else {
                double tmp4 = max(tmp1, tmp2 + tmp3);
                double tmp5 = max(tmp2, tmp1 + tmp3);

                if (tmp4 < tmp5) {
                    tmp1 = tmp4;
                    cx = V[i].first;

                } else {
                    tmp1 = tmp5;
                    cx = V[i + 1].first;
                }
            }
        }
        // debug(i, tmp1, cx);
        if (res > tmp1) {
            res = tmp1;
            res_x = cx;
        }
    }
    debug(res);
    cout << res_x << endl;
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