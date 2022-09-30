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

vector<vector<int>> fac;
const int maxn = 1e6;
void init() {
    fac.resize(maxn + 1);
    for (int i = 1; i <= maxn; i++) {
        for (int j = i; j <= maxn; j += i) {
            fac[j].push_back(i);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<vector<int>> num(maxn + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        num[a[i]].push_back(i);
    }

    vector<int> stk(n);
    int scnt = 0;
    vector<int> l_ge(n);
    // 左边第一个大于等于 a[i] 的下标
    for (int i = 0; i < n; i++) {
        while (scnt > 0 && a[stk[scnt - 1]] < a[i]) {
            scnt--;
        }
        if (scnt == 0) {
            l_ge[i] = -1;
        } else {
            l_ge[i] = stk[scnt - 1];
        }
        stk[scnt++] = i;
    }

    vector<int> r_g(n);
    // 右边第一个大于 a[i] 的下标
    scnt = 0;

    for (int i = n - 1; i >= 0; i--) {
        while (scnt > 0 && a[stk[scnt - 1]] <= a[i]) {
            scnt--;
        }
        if (scnt == 0) {
            r_g[i] = n;
        } else {
            r_g[i] = stk[scnt - 1];
        }
        stk[scnt++] = i;
    }

    vector<int> l_le(n);
    scnt = 0;
    for (int i = 0; i < n; i++) {
        while (scnt > 0 && a[stk[scnt - 1]] > a[i]) {
            scnt--;
        }
        if (scnt == 0) {
            l_le[i] = -1;
        } else {
            l_le[i] = stk[scnt - 1];
        }
        stk[scnt++] = i;
    }

    vector<int> l_l(n);
    scnt = 0;
    for (int i = 0; i < n; i++) {
        while (scnt > 0 && a[stk[scnt - 1]] >= a[i]) {
            scnt--;
        }
        if (scnt == 0) {
            l_l[i] = -1;
        } else {
            l_l[i] = stk[scnt - 1];
        }
        stk[scnt++] = i;
    }

    vector<int> r_l(n);
    scnt = 0;
    for (int i = n - 1; i >= 0; i--) {
        while (scnt > 0 && a[stk[scnt - 1]] >= a[i]) {
            scnt--;
        }
        if (scnt == 0) {
            r_l[i] = n;
        } else {
            r_l[i] = stk[scnt - 1];
        }
        stk[scnt++] = i;
    }
    // debug(l_ge);
    // debug(r_g);
    // debug(l_le);
    // debug(r_l);

    ll ans = 0;
    vector<int> now_idx(maxn + 1);
    for (int i = 0; i < n; i++) {
        int val = a[i];
        int left = l_ge[i] + 1, right = r_g[i] - 1;
        debug(i, left, right);
        // [left, right]
        ll sub_ans = 0;
        for (auto f : fac[val]) {
            if (num[f].size() && now_idx[f] - 1 < num[f].size() && now_idx[f] - 1 >= 0) {
                int the_idx = num[f][now_idx[f] - 1];
                // 最近的一个下标
                if (the_idx >= left) {
                    int left2 = l_l[the_idx] + 1;
                    int right2 = r_l[the_idx] - 1;
                    if (right2 >= i) {
                        debug(i, left2, right2);
                        sub_ans += 1LL * (the_idx - max(left, left2) + 1) * (min(right2, right) - i + 1);
                    }
                }
            }
            if (num[f].size() && now_idx[f] < num[f].size()) {
                int the_idx = num[f][now_idx[f]];
                if (the_idx <= right) {
                    int left2 = l_le[the_idx] + 1;
                    int right2 = r_l[the_idx] - 1;
                    if (left2 <= i) {
                        sub_ans += 1LL * (i - max(left, left2) + 1) * (min(right2, right) - the_idx + 1);
                    }
                }
            }
        }
        ans += sub_ans;
        debug(i, sub_ans);
        now_idx[val]++;
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}