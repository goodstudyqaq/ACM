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
    vector<int> p(n);
    vector<int> idx(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        idx[p[i]] = i;
    }

    int l = idx[0], r = idx[0];
    set<int> S;
    S.insert(0);
    int mex = 0;
    auto get_mex = [&]() {
        while (S.count(mex)) {
            mex++;
        }
        return mex;
    };

    ll ans = 0;
    while (get_mex() < n) {
        int the_mex = get_mex();
        int the_idx = idx[the_mex];
        if (the_idx < l) {
            for (int i = l; i > the_idx; i--) {
                S.insert(p[i]);
                int len = r - i + 1;
                if (len > 2 * the_mex) {
                    continue;
                }
                int have = 2 * the_mex - len;
                int tmp = min(n - 1, r + have) - r + 1;
                ans += tmp;
            }
            l = the_idx;
        } else {
            for (int i = r; i < the_idx; i++) {
                S.insert(p[i]);
                int len = i - l + 1;
                if (len > 2 * the_mex) {
                    continue;
                }

                int have = 2 * the_mex - len;
                int tmp = l - max(0, l - have) + 1;
                ans += tmp;
            }
            r = the_idx;
        }
        S.insert(p[the_idx]);
        // debug(ans);
    }
    cout << ans + 1 << endl;
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