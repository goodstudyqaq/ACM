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
    vector<int> a(n);
    int mx_a = 0;
    multiset<int> S;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx_a = max(mx_a, a[i]);
        S.insert(a[i]);
    }

    while (q--) {
        int c;
        cin >> c;
        if (mx_a >= c) {
            cout << 0 << '\n';
            continue;
        }

        vector<pii> tmp;
        int ans = 0;

        for (int i = 29; i >= 0; i--) {
            if (*S.rbegin() >= c) break;
            if ((c >> i) & 1) {
                int now_mx = *S.rbegin();
                debug(i, now_mx);
                if ((now_mx >> i) & 1) {
                    S.erase(S.find(now_mx));
                    S.insert(now_mx - (1 << i));
                    tmp.push_back({now_mx, -1});
                    tmp.push_back({now_mx - (1 << i), 1});
                } else {
                    ans += (1 << i) - now_mx;
                    S.erase(S.find(now_mx));
                    S.insert(0);
                    tmp.push_back({now_mx, -1});
                    tmp.push_back({0, 1});
                }
                c -= (1 << i);
            }
        }
        cout << ans << '\n';

        for (auto it : tmp) {
            if (it.second == -1) {
                S.insert(it.first);
            } 
        }
        for (auto it : tmp) {
            if (it.second == 1) {
                S.erase(S.find(it.first));
            }
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